/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 01:43:32 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/14 22:17:44 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

// Frees the cmd_and_params and cmd_path variables in the pipex struct.
void	child_free(struct s_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_and_params)
	{
		while (pipex->cmd_and_params[i])
		{
			free(pipex->cmd_and_params[i]);
			i++;
		}
		free(pipex->cmd_and_params);
		pipex->cmd_and_params = NULL;
	}
	if (pipex->cmd_path)
	{
		free(pipex->cmd_path);
		pipex->cmd_path = NULL;
	}
}

// Frees the paths variable in the pipex struct.
void	parent_free(struct s_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->paths)
	{
		while (pipex->paths[i])
		{
			free(pipex->paths[i]);
			i++;
		}
		free(pipex->paths);
		pipex->paths = NULL;
	}
}
