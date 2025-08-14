/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:16:16 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/14 19:51:14 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static void	dup2_and_err_check(int fd_1, int fd_2, struct s_pipex *pipex)
{
	if (dup2(fd_1, fd_2) == -1)
	{
		perror("dup2");
		child_free(pipex);
		close(pipex->pipe[READ]);
		close(pipex->outfile);
		exit(1);
	}
}

static void	outfile_err_check(struct s_pipex *pipex, char **av)
{
	if (pipex->outfile == -1)
	{
		perror(av[4]);
		child_free(pipex);
		close(pipex->pipe[READ]);
		exit(1);
	}
}

static void	get_cmd_and_params_and_err_check(struct s_pipex *pipex, char **av)
{
	pipex->cmd_and_params = ft_split(av[3], ' ');
	if (!pipex->cmd_and_params)
	{
		ft_fprintf(STDERR, "Error: cmd_and_params: malloc() failed.\n");
		child_free(pipex);
		close(pipex->pipe[READ]);
		close(pipex->outfile);
		exit(1);
	}
	if (!pipex->cmd_and_params[0])
	{
		ft_fprintf(STDERR, "Error: invalid command\n");
		child_free(pipex);
		close(pipex->pipe[READ]);
		close(pipex->outfile);
		exit(127);
	}
}

static void	get_cmd_path_and_err_check(struct s_pipex *pipex, char *cmd_name)
{
	pipex->cmd_path = get_cmd_path(pipex->paths, cmd_name, pipex);
	if (!pipex->cmd_path)
	{
		ft_fprintf(STDERR, "%s: command not found\n", cmd_name);
		child_free(pipex);
		close(pipex->pipe[READ]);
		close(pipex->outfile);
		exit(127);
	}
}

void	child_2(struct s_pipex pipex, char **av, char **envp)
{
	char	*cmd_name;

	close(pipex.pipe[WRITE]);
	outfile_err_check(&pipex, av);
	dup2_and_err_check(pipex.pipe[READ], STDIN, &pipex);
	dup2_and_err_check(pipex.outfile, STDOUT, &pipex);
	get_cmd_and_params_and_err_check(&pipex, av);
	cmd_name = pipex.cmd_and_params[0];
	get_cmd_path_and_err_check(&pipex, cmd_name);
	execve(pipex.cmd_path, pipex.cmd_and_params, envp);
	perror("execve");
	child_free(&pipex);
	close(pipex.pipe[READ]);
	close(pipex.outfile);
	exit(127);
}
