/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:49:36 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/12 01:47:55 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

// Exits with an error message if argument count 
void	if_args_invalid_do_exit(int ac, char **av)
{
	if (ac != 5)
	{
		ft_fprintf(STDERR, "Error: Invalid number of arguments.\nTry: ");
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
void	create_pipe_if_err_do_exit(struct s_pipex *pipex)
{
	if (pipe(pipex->pipe) == -1)
	{
		perror("Pipe");
		exit(1);
	}
}

void	cmd_paths_if_err_do_exit(struct s_pipex *pipex)
{
	if (pipex->cmd_paths == NULL)
	{
		ft_fprintf(2, "Error: cmd_paths: malloc() failed.");
		parent_free(pipex);
		exit(1);
	}
}

// Closes the file descriptors that are open in the parent process.
void	close_parent_fds(struct s_pipex *pipex)
{
	close(pipex->pipe[READ]);
	close(pipex->pipe[WRITE]);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
}
