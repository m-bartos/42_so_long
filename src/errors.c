/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:04:49 by mbartos           #+#    #+#             */
/*   Updated: 2023/12/22 01:14:32 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	error(void)
{
	ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}

void	error_argc(int argc)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error: Expecting 2 arg.\n", 2);
		ft_putstr_fd("Format: ./so_long MAP_NAME.ber\n", 1);
		ft_putstr_fd("Map has to be located in map folder.\n", 1);
		ft_putstr_fd("Try run with: ./so_long map1.ber\n", 1);
		exit(1);
	}
}
