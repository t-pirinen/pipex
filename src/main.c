/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:36:57 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/14 22:20:29 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

/*	Exits with an error message if argument count is incorrect or
	an argument is empty.		*/
static void	arg_validity_check(int ac, char **av)
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

/*	Gets the contents of the $PATH variable and turns it into an array
	of the individual possible paths and checks if the memory allocation
	in ft_split failed when creating the array.		*/
static void	get_cmd_paths_and_err_check(struct s_pipex *pipex, char **envp)
{
	pipex->paths = ft_split(find_paths(envp), ':');
	if (pipex->paths == NULL)
	{
		ft_fprintf(2, "Error: paths: malloc() failed.");
		parent_free(pipex);
		exit(1);
	}
}

/*	Creates a one-way communication channel (pipe) in the pipex struct.
	Exits with a perror message if pipe creation fails.		*/
static void	create_pipe_and_err_check(struct s_pipex *pipex)
{
	if (pipe(pipex->pipe) == -1)
	{
		perror("pipe");
		parent_free(pipex);
		exit(1);
	}
}

// Closes the file descriptors that are open in the parent process.
static void	close_parent_fds(struct s_pipex *pipex)
{
	close(pipex->pipe[READ]);
	close(pipex->pipe[WRITE]);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
}

int	main(int ac, char **av, char **envp)
{
	struct s_pipex	pipex;
	int				child2_status;

	ft_memset(&pipex, 0, sizeof(pipex));
	arg_validity_check(ac, av);
	get_cmd_paths_and_err_check(&pipex, envp);
	create_pipe_and_err_check(&pipex);
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child_1(pipex, av, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child_2(pipex, av, envp);
	close_parent_fds(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, &child2_status, 0);
	parent_free(&pipex);
	return (child2_status >> 8);
}
