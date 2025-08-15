/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:36:57 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/15 13:13:44 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

int	main(int ac, char **av, char **envp)
{
	struct s_pipex	pipex;
	int				child2_status;

	ft_memset(&pipex, 0, sizeof(pipex));
	arg_validity_check(ac, av);
	get_paths_and_err_check(&pipex, envp);
	create_pipe_and_err_check(&pipex);
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	pipex.pid1 = fork();
	fork_err_check(&pipex);
	if (pipex.pid1 == 0)
		child_1(pipex, av, envp);
	pipex.pid2 = fork();
	fork_err_check(&pipex);
	if (pipex.pid2 == 0)
		child_2(pipex, av, envp);
	close_parent_fds(&pipex);
	if (waitpid(pipex.pid1, NULL, 0) == -1)
		waitpid_failed(&pipex);
	if (waitpid(pipex.pid2, &child2_status, 0) == -1)
		waitpid_failed(&pipex);
	parent_free(&pipex);
	return (child2_status >> 8);
}
