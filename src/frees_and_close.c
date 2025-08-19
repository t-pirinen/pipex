/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_and_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 01:43:32 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/19 14:19:51 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static void	paths_free(t_child *child)
{
	int	i;

	i = 0;
	if (child->paths)
	{
		while (child->paths[i])
		{
			free(child->paths[i]);
			i++;
		}
		free(child->paths);
		child->paths = NULL;
	}
}

static void	cmd_and_params_free(t_child *child)
{
	int	i;

	i = 0;
	if (child->cmd_and_params)
	{
		while (child->cmd_and_params[i])
		{
			free(child->cmd_and_params[i]);
			i++;
		}
		free(child->cmd_and_params);
		child->cmd_and_params = NULL;
	}
}

void	child_free(t_child *child)
{
	paths_free(child);
	cmd_and_params_free(child);
	if (child->cmd_path)
	{
		free(child->cmd_path);
		child->cmd_path = NULL;
	}
}

// Closes the file descriptors that are open in the parent process.
void	close_fds(t_parent *parent)
{
	if (parent->pipe[READ] >= 0)
		close(parent->pipe[READ]);
	if (parent->pipe[WRITE] >= 0)
		close(parent->pipe[WRITE]);
	if (parent->infile >= 0)
		close(parent->infile);
	if (parent->outfile >= 0)
		close(parent->outfile);
}
