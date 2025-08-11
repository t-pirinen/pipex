/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 01:43:32 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/12 01:43:45 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

// Frees the cmd_and_args and full_cmd_path variables in the pipex struct.
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

// Frees the cmd_paths variable in the pipex struct.
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
