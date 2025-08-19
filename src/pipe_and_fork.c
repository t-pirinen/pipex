/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:31:05 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/19 14:13:48 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

/*	Creates a one-way communication channel (pipe) in the parent struct.
	Exits with a perror message if pipe creation fails.		*/
void	create_pipe_and_err_check(t_parent *parent)
{
	if (pipe(parent->pipe) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

// Checks for fork() failure and exits accordingly.
void	fork_err_check(t_parent *parent)
{
	if (parent->pid1 == -1 || parent->pid2 == -1)
	{
		if (parent->pid1 == -1)
			perror("pid1 fork failed");
		else
			perror("pid2 fork failed");
		close_fds(parent);
		exit(1);
	}
}
