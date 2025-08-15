/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:35:55 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/15 13:59:17 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

/*	Exits with an error message if argument count is incorrect or
	an argument is empty.		*/
void	arg_validity_check(int ac, char **av)
{
	if (ac != 5)
	{
		ft_fprintf(STDERR, "Error: Invalid number of arguments.\n");
		ft_fprintf(STDERR, "Try: ");
		ft_fprintf(STDERR, "./pipex \"file1\" \"cmd1\" \"cmd2\" \"file2\"\n");
		exit(1);
	}
	if (!av[1][0] || !av[2][0] || !av[3][0] || !av[4][0])
	{
		ft_fprintf(STDERR, "Error: Empty argument.\n");
		exit(1);
	}
}

/*	Creates a one-way communication channel (pipe) in the pipex struct.
	Exits with a perror message if pipe creation fails.		*/
void	create_pipe_and_err_check(struct s_pipex *pipex)
{
	if (pipe(pipex->pipe) == -1)
	{
		perror("pipe");
		parent_free(pipex);
		exit(1);
	}
}

// Checks for fork() failure and exits accordingly.
void	fork_err_check(struct s_pipex *pipex)
{
	if (pipex->pid1 == -1 || pipex->pid2 == -1)
	{
		if (pipex->pid1 == -1)
			perror("pid1 fork failed");
		else
			perror("pid2 fork failed");
		close_parent_fds(pipex);
		parent_free(pipex);
		exit(1);
	}
}

// Exits appropriately when waitpid fails.
void	waitpid_failed(struct s_pipex *pipex)
{
	perror("wait failed");
	close_parent_fds(pipex);
	parent_free(pipex);
	exit(1);
}
