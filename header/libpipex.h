/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:37:20 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/16 17:09:47 by tpirinen         ###   ########.fr       */
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

typedef struct t_parent
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe[2];
	int		infile;
	int		outfile;
}	t_parent;

typedef struct s_child
{
	char	**paths;
	char	**cmd_and_params;
	char	*cmd_path;
	char	*cmd_name;
}	t_child;

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
void	create_pipe_and_err_check(t_parent *parent);
void	fork_err_check(t_parent *parent);
void	waitpid_failed(t_parent *parent);

void	get_paths_and_err_check(t_child *child, char **envp);
void	get_cmd_path(t_child *child, char **paths);

void	child_1(t_parent parent, char **av, char **envp);
void	child_2(t_parent parent, char **av, char **envp);

void	child_free(t_child *child);
void	close_parent_fds(t_parent *pipex);

#endif
