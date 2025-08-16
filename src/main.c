/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:36:57 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/16 15:46:57 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

int	main(int ac, char **av, char **envp)
{
	t_parent	parent;
	int			child2_status;

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
	close_parent_fds(&parent);
	if (waitpid(parent.pid1, NULL, 0) == -1)
		waitpid_failed(&parent);
	if (waitpid(parent.pid2, &child2_status, 0) == -1)
		waitpid_failed(&parent);
	return (child2_status >> 8);
}
