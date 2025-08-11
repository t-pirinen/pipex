/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:37:20 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/12 01:46:28 by tpirinen         ###   ########.fr       */
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

void	if_args_invalid_do_exit(int ac, char **av);
void	create_pipe_if_err_do_exit(struct s_pipex *pipex);
void	cmd_paths_if_err_do_exit(struct s_pipex *pipex);

char	*find_path(char **envp);
char	*get_full_cmd_path(char **paths, char *cmd_name, struct s_pipex *pipex);

void	child_one(struct s_pipex pipex, char **av, char **envp);
void	child_two(struct s_pipex pipex, char **av, char **envp);

void	parent_free(struct s_pipex *pipex);
void	child_free(struct s_pipex *pipex);

void	close_parent_fds(struct s_pipex *pipex);

#endif
