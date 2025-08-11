/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:36:57 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/12 01:45:35 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

int	main(int ac, char **av, char **envp)
{
	struct s_pipex	pipex;
	int				status1;
	int				status2;

	ft_memset(&pipex, 0, sizeof * &pipex);
	if_args_invalid_do_exit(ac, av);
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	create_pipe_if_err_do_exit(&pipex);
	pipex.cmd_paths = ft_split(find_path(envp), ':');
	cmd_paths_if_err_do_exit(&pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child_one(pipex, av, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child_two(pipex, av, envp);
	close_parent_fds(&pipex);
	waitpid(pipex.pid1, &status1, 0);
	waitpid(pipex.pid2, &status2, 0);
	parent_free(&pipex);
	return (status2 >> 8);
}
