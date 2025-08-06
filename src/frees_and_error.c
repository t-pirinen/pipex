/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_and_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:49:36 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/01 18:57:30 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

void	parent_free(struct s_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

void	child_free(struct s_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_and_args[i])
	{
		free(pipex->cmd_and_args[i]);
		i++;
	}
	free(pipex->cmd_and_args);
	free(pipex->full_cmd_path);
}

void	perror_and_exit(char *err)
{
	perror(err);
	exit(1);
}
