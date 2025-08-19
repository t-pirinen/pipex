/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:36:57 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/19 14:12:50 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static void	wait_for_children(t_parent *parent)
{
	int		child_count;
	int		status;
	pid_t	pid;

	child_count = 2;
	pid = 0;
	while (child_count)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			waitpid_failed(parent);
		if (pid == parent->pid2)
			parent->exit_code = status;
		child_count--;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_parent	parent;

	ft_memset(&parent, 0, sizeof(parent));
	arg_validity_check(ac, av);
	create_pipe_and_err_check(&parent);
	parent.infile = open(av[1], O_RDONLY);
	parent.outfile = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	parent.pid1 = fork();
	fork_err_check(&parent);
	if (parent.pid1 == 0)
		child_1(parent, av, envp);
	parent.pid2 = fork();
	fork_err_check(&parent);
	if (parent.pid2 == 0)
		child_2(parent, av, envp);
	close_fds(&parent);
	wait_for_children(&parent);
	return (parent.exit_code >> 8);
}
