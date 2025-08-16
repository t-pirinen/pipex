/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:56:37 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/16 17:06:10 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static void	infile_err_check(t_parent *parent, char **av)
{
	if (parent->infile == -1)
	{
		perror(av[1]);
		close(parent->pipe[WRITE]);
		exit(1);
	}
}

static void	dup2_and_err_check(int fd_1, int fd_2, t_parent *parent)
{
	if (dup2(fd_1, fd_2) == -1)
	{
		perror("dup2");
		close(parent->pipe[WRITE]);
		close(parent->infile);
		exit(1);
	}
}

static void	cmd_params_err_check(t_parent *parent, t_child *child, char **av)
{
	if (!child->cmd_and_params)
	{
		ft_fprintf(STDERR, "Error: cmd_and_params: malloc() failed\n");
		child_free(child);
		close(parent->pipe[WRITE]);
		close(parent->infile);
		exit(1);
	}
	if (!child->cmd_and_params[0])
	{
		ft_fprintf(STDERR, "Error: invalid command\n");
		close(parent->pipe[WRITE]);
		close(parent->infile);
		exit(127);
	}
}

static void	get_cmd_path_and_err_check(t_parent *parent, t_child *child)
{
	child->cmd_name = child->cmd_and_params[0];
	get_cmd_path(child, child->paths);
	if (!child->cmd_path)
	{
		ft_fprintf(STDERR, "%s: command not found\n", child->cmd_name);
		child_free(child);
		close(parent->pipe[WRITE]);
		close(parent->infile);
		exit(127);
	}
}

void	child_1(t_parent parent, char **av, char **envp)
{
	t_child	child;

	close(parent.pipe[READ]);
	infile_err_check(&parent, av);
	dup2_and_err_check(parent.pipe[WRITE], STDOUT, &parent);
	dup2_and_err_check(parent.infile, STDIN, &parent);
	get_paths_and_err_check(&child, envp);
	child.cmd_and_params = ft_split(av[2], ' ');
	cmd_params_err_check(&parent, &child, av);
	get_cmd_path_and_err_check(&parent, &child);
	execve(child.cmd_path, child.cmd_and_params, envp);
	perror("execve");
	child_free(&child);
	close(parent.pipe[WRITE]);
	close(parent.infile);
	exit(127);
}
