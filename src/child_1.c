/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:56:37 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/18 19:01:32 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static void	infile_err_check(t_parent *parent, char **av)
{
	if (parent->infile == -1)
	{
		perror(av[1]);
		close_child_fds(parent);
		exit(1);
	}
}

static void	dup2_and_err_check(int fd_1, int fd_2, t_parent *parent)
{
	if (dup2(fd_1, fd_2) == -1)
	{
		perror("dup2");
		close_child_fds(parent);
		exit(1);
	}
}

static void	cmd_params_err_check(t_parent *parent, t_child *child)
{
	if (!child->cmd_and_params)
	{
		write(STDERR, "Error: cmd_and_params: malloc() failed.\n", 40);
		child_free(child);
		close_child_fds(parent);
		exit(1);
	}
	if (!child->cmd_and_params[0])
	{
		write(STDERR, "Error: command not found.\n", 26);
		child_free(child);
		close_child_fds(parent);
		exit(127);
	}
}

static void	cmd_path_err_check(t_parent *parent, t_child *child)
{
	if (!child->cmd_path)
	{
		write(STDERR, child->cmd_name, ft_strlen(child->cmd_name));
		write(STDERR, ": command not found\n", 20);
		child_free(child);
		close_child_fds(parent);
		exit(127);
	}
}

void	child_1(t_parent parent, char **av, char **envp)
{
	t_child	child;

	ft_memset(&child, 0, sizeof(child));
	close(parent.pipe[READ]);
	close(parent.outfile);
	infile_err_check(&parent, av);
	dup2_and_err_check(parent.pipe[WRITE], STDOUT, &parent);
	dup2_and_err_check(parent.infile, STDIN, &parent);
	get_paths(&parent, &child, envp);
	child.cmd_and_params = ft_split(av[2], ' ');
	cmd_params_err_check(&parent, &child);
	get_cmd_path(&parent, &child, child.paths);
	cmd_path_err_check(&parent, &child);
	close_child_fds(&parent);
	execve(child.cmd_path, child.cmd_and_params, envp);
	perror("execve");
	child_free(&child);
	close_child_fds(&parent);
	close(parent.pipe[WRITE]);
	close(parent.infile);
	exit(126);
}
