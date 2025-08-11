/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:37:20 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/11 16:37:05 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPIPEX_H
# define LIBPIPEX_H

# include "../libft/libft.h"

// for pid_t definition
# include <sys/types.h>

// for waitpid()
# include <sys/wait.h>

// for open() and it's file access modes
# include <fcntl.h>

// for perror()
# include <stdio.h>

struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe[2];
	int		infile;
	int		outfile;
	char	**cmd_paths;
	char	**cmd_and_args;
	char	*full_cmd_path;
};

enum e_pipe
{
	READ,
	WRITE
};

enum e_in_out_err
{
	STDIN,
	STDOUT,
	STDERR
};

void	first_child(struct s_pipex pipex, char **av, char **envp);
void	second_child(struct s_pipex pipex, char **av, char **envp);

void	parent_free(struct s_pipex *pipex);
void	child_free(struct s_pipex *pipex);

void	perror_and_exit(char *err);

#endif
