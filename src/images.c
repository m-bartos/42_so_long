/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:06:12 by mbartos           #+#    #+#             */
/*   Updated: 2023/12/22 01:06:27 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	img_and_tex(char *path, mlx_t *mlx,
					mlx_texture_t **tex, mlx_image_t **img)
{
	*tex = mlx_load_png(path);
	if (!*tex)
		error();
	*img = mlx_texture_to_image(mlx, *tex);
	if (!*img)
		error();
	mlx_delete_texture(*tex);
}

t_images	*load_images(mlx_t *mlx)
{
	t_images	*images;

	images = (t_images *) malloc(1 * sizeof(t_images));
	if (!images)
		error();
	img_and_tex("./img/Wizard_Man_64x64.png", mlx, &images->player_tex, &images->player_img);
	img_and_tex("./img/Wall_64x64.png", mlx, &images->wall_tex, &images->wall_img);
	img_and_tex("./img/Consumable_64x64.png", mlx, &images->consumable_tex, &images->consumable_img);
	img_and_tex("./img/gate_closed_64x64.png", mlx, &images->exit_close_tex, &images->exit_close_img);
	img_and_tex("./img/gate_opened_64x64.png", mlx, &images->exit_open_tex, &images->exit_open_img);
	img_and_tex("./img/skull_64x64-3.png", mlx, &images->enemy_tex, &images->enemy_img);
	return (images);
}

void	ft_put_sprite(mlx_t *mlx, mlx_image_t *img, t_map *map, char symbol)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map->array[y])
	{
		x = 0;
		while (map->array[y][x])
		{
			if (map->array[y][x] == symbol)
			{
				if (mlx_image_to_window(mlx, img, x * BLOCK_W, y * BLOCK_H) < 0)
					error();
			}
			x++;
		}
		y++;
	}
}
