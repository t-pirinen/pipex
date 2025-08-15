/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:37:20 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/15 13:14:23 by tpirinen         ###   ########.fr       */
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
	char	**paths;
	char	**cmd_and_params;
	char	*cmd_path;
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

void	arg_validity_check(int ac, char **av);
void	get_paths_and_err_check(struct s_pipex *pipex, char **envp);
void	create_pipe_and_err_check(struct s_pipex *pipex);
void	fork_err_check(struct s_pipex *pipex);
void	waitpid_failed(struct s_pipex *pipex);

char	*find_path(char **envp);
char	*get_cmd_path(struct s_pipex *pipex, char **paths, char *cmd_name);

void	child_1(struct s_pipex pipex, char **av, char **envp);
void	child_2(struct s_pipex pipex, char **av, char **envp);

void	child_free(struct s_pipex *pipex);
void	parent_free(struct s_pipex *pipex);
void	close_parent_fds(struct s_pipex *pipex);

#endif
