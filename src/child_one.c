/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:56:37 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/12 01:39:21 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static void	infile_if_err_do_exit(struct s_pipex *pipex, char **av)
{
	if (pipex->infile == -1)
	{
		close(pipex->pipe[WRITE]);
		child_free(pipex);
		perror(av[1]);
		exit(1);
	}
}

static void	cmd_and_args_if_err_do_exit(struct s_pipex *pipex)
{
	if (!pipex->cmd_and_args)
	{
		ft_fprintf(STDERR, "Error: cmd_and_args: malloc() failed\n");
		child_free(pipex);
		exit(1);
	}
	if (!pipex->cmd_and_args[0])
	{
		ft_fprintf(STDERR, "Error: invalid command\n");
		child_free(pipex);
		exit(127);
	}
}

static void	full_cmd_path_if_err_do_exit(struct s_pipex *pipex, char *cmd_name)
{
	if (!pipex->full_cmd_path)
	{
		ft_fprintf(STDERR, "%s: command not found\n", cmd_name);
		child_free(pipex);
		close(pipex->pipe[WRITE]);
		close(pipex->infile);
		exit(127);
	}
}

void	child_one(struct s_pipex pipex, char **av, char **envp)
{
	char	*cmd_name;

	dup2(pipex.pipe[WRITE], STDOUT);
	close(pipex.pipe[READ]);
	infile_if_err_do_exit(&pipex, av);
	dup2(pipex.infile, STDIN);
	pipex.cmd_and_args = ft_split(av[2], ' ');
	cmd_and_args_if_err_do_exit(&pipex);
	cmd_name = pipex.cmd_and_args[0];
	pipex.full_cmd_path = get_full_cmd_path(pipex.cmd_paths, cmd_name, &pipex);
	full_cmd_path_if_err_do_exit(&pipex, cmd_name);
	execve(pipex.full_cmd_path, pipex.cmd_and_args, envp);
}
