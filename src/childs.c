/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:56:37 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/11 19:09:21 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static char	*get_full_cmd_path(char **paths, char *cmd_name)
{
	char	*temp;
	char	*full_cmd_path;

	if (!paths || !cmd_name)
		return (NULL);
	if (access(cmd_name, F_OK) == 0)
		return (ft_strdup(cmd_name));
	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		full_cmd_path = ft_strjoin(temp, cmd_name);
		free(temp);
		if (access(full_cmd_path, F_OK) == 0)
			return (full_cmd_path);
		free(full_cmd_path);
		paths++;
	}
	return (NULL);
}

void	first_child(struct s_pipex pipex, char **av, char **envp)
{
	char	*cmd_name;

	dup2(pipex.pipe[WRITE], STDOUT);
	close(pipex.pipe[READ]);
	if (pipex.infile < 0)
	{
		close(pipex.pipe[WRITE]);
		child_free(&pipex);
		perror(av[1]);
		exit(1);
	}
	dup2(pipex.infile, STDIN);
	pipex.cmd_and_args = ft_split(av[2], ' ');
	if (!pipex.cmd_and_args || !pipex.cmd_and_args[0])
	{
		ft_fprintf(STDERR, "Error: invalid command\n");
		child_free(&pipex);
		exit(127);
	}
	cmd_name = pipex.cmd_and_args[0];
	pipex.full_cmd_path = get_full_cmd_path(pipex.cmd_paths, cmd_name);
	if (!pipex.full_cmd_path)
	{
		ft_fprintf(STDERR, "%s: command not found\n", cmd_name);
		child_free(&pipex);
		close(pipex.pipe[WRITE]);
		close(pipex.infile);
		exit(127);
	}
	execve(pipex.full_cmd_path, pipex.cmd_and_args, envp);
}

void	second_child(struct s_pipex pipex, char **av, char **envp)
{
	char	*cmd_name;

	dup2(pipex.pipe[READ], STDIN);
	close(pipex.pipe[WRITE]);
	if (pipex.outfile < 0)
	{
		perror(av[4]);
		close(pipex.pipe[READ]);
        child_free(&pipex);
        exit(1);
	}
	if (dup2(pipex.outfile, STDOUT) == -1)
	{
		perror(av[4]);
		close(pipex.pipe[READ]);
		close(pipex.outfile);
        child_free(&pipex);
        exit(1);
	}
	pipex.cmd_and_args = ft_split(av[3], ' ');
	if (!pipex.cmd_and_args || !pipex.cmd_and_args[0])
	{
		ft_fprintf(STDERR, "Error: invalid command\n");
		child_free(&pipex);
		exit(127);
	}
	cmd_name = pipex.cmd_and_args[0];
	pipex.full_cmd_path = get_full_cmd_path(pipex.cmd_paths, cmd_name);
	if (!pipex.full_cmd_path)
	{
		ft_fprintf(STDERR, "%s: command not found\n", cmd_name);
		child_free(&pipex);
		close(pipex.pipe[READ]);
		close(pipex.outfile);
		exit(127);
	}
	execve(pipex.full_cmd_path, pipex.cmd_and_args, envp);
}
