/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:56:37 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/01 20:22:00 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static char	*get_full_cmd_path(char **paths, char *cmd_name)
{
	char	*temp;
	char	*full_cmd_path;

	if (!paths || !cmd_name)
		return (NULL);
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

	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_and_args = ft_split(av[2], ' ');
	if (!pipex.cmd_and_args || !pipex.cmd_and_args[0])
	{
		write(2, "Error: invalid command\n", 23);
		child_free(&pipex);
		exit(1);
	}
	cmd_name = pipex.cmd_and_args[0];
	pipex.full_cmd_path = get_full_cmd_path(pipex.cmd_paths, cmd_name);
	if (!pipex.full_cmd_path)
	{
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": command not found\n", 20);
		child_free(&pipex);
		close(pipex.pipe[1]);
		close(pipex.infile);
		exit(1);
	}
	execve(pipex.full_cmd_path, pipex.cmd_and_args, envp);
}

void	second_child(struct s_pipex pipex, char **av, char **envp)
{
	char	*cmd_name;

	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_and_args = ft_split(av[3], ' ');
	if (!pipex.cmd_and_args || !pipex.cmd_and_args[0])
	{
		write(2, "Error: invalid command\n", 23);
		child_free(&pipex);
		exit(1);
	}
	cmd_name = pipex.cmd_and_args[0];
	pipex.full_cmd_path = get_full_cmd_path(pipex.cmd_paths, cmd_name);
	if (!pipex.full_cmd_path)
	{
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": command not found\n", 20);
		child_free(&pipex);
		close(pipex.pipe[0]);
		close(pipex.outfile);
		exit(1);
	}
	execve(pipex.full_cmd_path, pipex.cmd_and_args, envp);
}
