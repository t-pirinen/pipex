/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_and_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:49:36 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/11 22:55:27 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

void	parent_free(struct s_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_paths)
	{
		while (pipex->cmd_paths[i])
		{
			free(pipex->cmd_paths[i]);
			i++;
		}
		free(pipex->cmd_paths);
		pipex->cmd_paths = NULL;
	}
}

void	child_free(struct s_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_and_args)
	{
		while (pipex->cmd_and_args[i])
		{
			free(pipex->cmd_and_args[i]);
			i++;
		}
		free(pipex->cmd_and_args);
		pipex->cmd_and_args = NULL;
	}
	if (pipex->full_cmd_path)
	{
		free(pipex->full_cmd_path);
		pipex->full_cmd_path = NULL;
	}
}

void	perror_and_exit(char *err)
{
	perror(err);
	exit(1);
}
