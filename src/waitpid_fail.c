/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid_fail.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:35:55 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/18 19:11:10 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

// Exits appropriately when waitpid fails.
void	waitpid_failed(t_parent *parent)
{
	perror("wait failed");
	close_parent_fds(parent);
	exit(1);
}
