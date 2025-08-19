/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:14:06 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/19 14:13:14 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

/*	Gets the contents of the $PATH variable and turns it into an array
	of the individual possible paths additionally checking if the
	memory allocation in ft_split failed when creating the array.		*/
void	get_paths(t_parent *parent, t_child *child, char **envp)
{
	char	*path;

	while (*envp && ft_strncmp("PATH=", *envp, 5) != 0)
		envp++;
	if (*envp == NULL)
	{
		child->paths = NULL;
		return ;
	}
	path = *envp + 5;
	child->paths = ft_split(path, ':');
	if (child->paths == NULL)
	{
		write(STDERR, "Error: paths: malloc() failed.\n", 31);
		child_free(child);
		close_fds(parent);
		exit(1);
	}
}
