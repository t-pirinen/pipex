/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:32:28 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/19 14:13:36 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

static int	is_cmd_name_a_path(t_parent *parent, t_child *child)
{
	char	*cmd_name;

	cmd_name = child->cmd_name;
	if (ft_strchr(cmd_name, '/') == NULL)
		return (false);
	if (access(child->cmd_name, F_OK) == 0)
	{
		child->cmd_path = child->cmd_name;
		return (true);
	}
	write(STDERR, "Error: no such file or directory: \n", 35);
	write(STDERR, child->cmd_name, ft_strlen(child->cmd_name));
	write(STDERR, "\n", 1);
	child_free(child);
	close_fds(parent);
	exit(127);
}

static void	no_environment_check(t_parent *parent, t_child *child)
{
	if (child->paths == NULL)
	{
		write(STDERR, child->cmd_name, ft_strlen(child->cmd_name));
		write(STDERR, ": command not found\n", 20);
		child_free(child);
		close_fds(parent);
		exit(127);
	}
}

/*	Tests access to the given command and returns immediately when a valid path
	is found e.g. /usr/bin/ls. If the cmd_name is a valid path
	assigns cmd_name to cmd_path and returns. If no valid path is found,
	sets cmd_path to NULL.		*/
void	get_cmd_path(t_parent *parent, t_child *child, char **paths)
{
	char	*path_with_slash;

	child->cmd_name = child->cmd_and_params[0];
	if (is_cmd_name_a_path(parent, child) == true)
		return ;
	no_environment_check(parent, child);
	while (*paths)
	{
		path_with_slash = ft_strjoin(*paths, "/");
		child->cmd_path = ft_strjoin(path_with_slash, child->cmd_name);
		if (child->cmd_path == NULL)
		{
			write(STDERR, "Error: cmd_path: malloc() failed.\n", 34);
			child_free(child);
			close_fds(parent);
			exit(1);
		}
		free(path_with_slash);
		if (access(child->cmd_path, F_OK) == 0)
			return ;
		free(child->cmd_path);
		paths++;
	}
	child->cmd_path = NULL;
}
