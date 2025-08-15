/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:14:06 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/15 13:59:41 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

// Returns a pointer to the memory which holds the contents of $PATH.
static char	*find_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp + 5);
		envp++;
	}
	ft_fprintf(STDERR, "$PATH not found");
	exit(1);
}

/*	Gets the contents of the $PATH variable and turns it into an array
	of the individual possible paths and checks if the memory allocation
	in ft_split failed when creating the array.		*/
void	get_paths_and_err_check(struct s_pipex *pipex, char **envp)
{
	pipex->paths = ft_split(find_path(envp), ':');
	if (pipex->paths == NULL)
	{
		ft_fprintf(2, "Error: paths: malloc() failed.");
		exit(1);
	}
}

/*	Tests access to the given command and returns the full command path
	when access to command is found e.g. /usr/bin/ls.
	Returns NULL when command isn't accessible.		*/
char	*get_cmd_path(struct s_pipex *pipex, char **paths, char *cmd_name)
{
	char	*path_with_slash;
	char	*cmd_path;

	if (!paths || !cmd_name)
		return (NULL);
	if (access(cmd_name, F_OK) == 0)
		return (ft_strdup(cmd_name));
	while (*paths)
	{
		path_with_slash = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(path_with_slash, cmd_name);
		if (cmd_path == NULL)
		{
			ft_fprintf(STDERR, "Error: cmd_path: malloc() failed.");
			child_free(pipex);
			exit(1);
		}
		free(path_with_slash);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		paths++;
	}
	return (NULL);
}
