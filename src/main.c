/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:36:57 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/01 20:11:20 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	main(int ac, char **av, char **envp)
{
	struct s_pipex	pipex;

	ft_memset(&pipex, 0, sizeof * &pipex);
	if (ac != 5)
		return (ft_error_msg("Invalid number of arguments.\n", 1));
	pipex.infile = open(av[1], O_RDONLY);
	if (pipex.infile < 0)
		perror_and_exit(av[1]);
	pipex.outfile = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pipex.outfile < 0)
		perror_and_exit(av[4]);
	if (pipe(pipex.pipe) < 0)
		perror_and_exit("Pipe");
	pipex.cmd_paths = ft_split(find_path(envp), ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, av, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, av, envp);
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
}
