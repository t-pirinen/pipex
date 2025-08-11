/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:14:06 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/12 01:39:31 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

// Returns a pointer to the memory which holds the contents of $PATH.
char	*find_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

/*	Tests access to the given command and returns the full command path
	when access to command is found e.g. /usr/bin/ls.
	Returns NULL when command isn't accessible.		*/
char	*get_full_cmd_path(char **paths, char *cmd_name, struct s_pipex *pipex)
{
	char	*path_with_slash;
	char	*full_cmd_path;

	if (!paths || !cmd_name)
		return (NULL);
	if (access(cmd_name, F_OK) == 0)
		return (ft_strdup(cmd_name));
	while (*paths)
	{
		path_with_slash = ft_strjoin(*paths, "/");
		full_cmd_path = ft_strjoin(path_with_slash, cmd_name);
		if (full_cmd_path == NULL)
		{
			ft_fprintf(STDERR, "Error: full_cmd_path: malloc() failed.");
			child_free(pipex);
			exit(1);
		}
		free(path_with_slash);
		if (access(full_cmd_path, F_OK) == 0)
			return (full_cmd_path);
		free(full_cmd_path);
		paths++;
	}
	return (NULL);
}
