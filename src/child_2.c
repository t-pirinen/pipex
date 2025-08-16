/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:16:16 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/16 17:06:20 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static void	outfile_err_check(t_parent *parent, char **av)
{
	if (parent->outfile == -1)
	{
		perror(av[4]);
		close(parent->pipe[READ]);
		exit(1);
	}
}

static void	dup2_and_err_check(int fd_1, int fd_2, t_parent *parent)
{
	if (dup2(fd_1, fd_2) == -1)
	{
		perror("dup2");
		close(parent->pipe[READ]);
		close(parent->outfile);
		exit(1);
	}
}

static void	cmd_params_err_check(t_parent *parent, t_child *child, char **av)
{
	if (!child->cmd_and_params)
	{
		ft_fprintf(STDERR, "Error: cmd_and_params: malloc() failed.\n");
		close(parent->pipe[READ]);
		close(parent->outfile);
		exit(1);
	}
	if (!child->cmd_and_params[0])
	{
		ft_fprintf(STDERR, "Error: invalid command\n");
		close(parent->pipe[READ]);
		close(parent->outfile);
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
		close(parent->pipe[READ]);
		close(parent->outfile);
		exit(127);
	}
}

void	child_2(t_parent parent, char **av, char **envp)
{
	t_child	child;

	ft_memset(&child, 0, sizeof(child));
	close(parent.pipe[WRITE]);
	outfile_err_check(&parent, av);
	dup2_and_err_check(parent.pipe[READ], STDIN, &parent);
	dup2_and_err_check(parent.outfile, STDOUT, &parent);
	get_paths_and_err_check(&child, envp);
	child.cmd_and_params = ft_split(av[3], ' ');
	cmd_params_err_check(&parent, &child, av);
	get_cmd_path_and_err_check(&parent, &child);
	execve(child.cmd_path, child.cmd_and_params, envp);
	perror("execve");
	close(parent.pipe[READ]);
	close(parent.outfile);
	exit(127);
}
