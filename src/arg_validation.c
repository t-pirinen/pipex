/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpirinen <tpirinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:30:31 by tpirinen          #+#    #+#             */
/*   Updated: 2025/08/18 17:54:24 by tpirinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libpipex.h"

/*	Exits with an error message if argument count is incorrect or
	an argument is empty.		*/
void	arg_validity_check(int ac, char **av)
{
	if (ac != 5)
	{
		write(STDERR, "Error: Invalid number of arguments.\n"
			"Try: ./parent \"file1\" \"cmd1\" \"cmd2\" \"file2\"\n", 80);
		exit(1);
	}
	if (!av[1][0] || !av[2][0] || !av[3][0] || !av[4][0])
	{
		write(STDERR, "Error: Empty argument.\n", 23);
		exit(1);
	}
}
