/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:36:57 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/11 19:14:22 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static char	*find_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	struct s_pipex	pipex;
	int				status1;
	int				status2;

	ft_memset(&pipex, 0, sizeof * &pipex);
	if (ac != 5)
		return (ft_error_msg("Error: Invalid number of arguments.\n", 1));
	if (!av[1][0] || !av[2][0] || !av[3][0] || !av[4][0])
        return (ft_error_msg("Error: Empty argument.\n", 1));
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (pipex.outfile < 0)
		perror(av[4]);
	if (pipe(pipex.pipe) == -1)
		perror_and_exit("Pipe");
	pipex.cmd_paths = ft_split(find_path(envp), ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, av, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, av, envp);
	close(pipex.pipe[READ]);
	close(pipex.pipe[WRITE]);
	if (pipex.infile >= 0)
		close(pipex.infile);
	if (pipex.outfile >= 0)
		close(pipex.outfile);
	waitpid(pipex.pid1, &status1, 0);
	waitpid(pipex.pid2, &status2, 0);
	parent_free(&pipex);
	return(status2 >> 8);
}
