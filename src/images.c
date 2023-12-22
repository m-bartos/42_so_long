/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:06:12 by mbartos           #+#    #+#             */
/*   Updated: 2023/12/22 11:20:04 by mbartos          ###   ########.fr       */
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
	t_images	*imgs;

	imgs = (t_images *) malloc(1 * sizeof(t_images));
	if (!imgs)
		error();
	img_and_tex("./img/player.png", mlx, &imgs->player_tex, &imgs->player_img);
	img_and_tex("./img/wall.png", mlx, &imgs->wall_tex, &imgs->wall_img);
	img_and_tex("./img/consum.png", mlx, &imgs->consum_tex, &imgs->consum_img);
	img_and_tex("./img/ex_clse.png", mlx, &imgs->ex_cls_tex, &imgs->ex_cls_img);
	img_and_tex("./img/ex_open.png", mlx, &imgs->ex_opn_tex, &imgs->ex_opn_img);
	img_and_tex("./img/skull.png", mlx, &imgs->enemy_tex, &imgs->enemy_img);
	return (imgs);
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

void	put_score(t_game *game)
{
	char	*old_str;
	char	*str_moves;

	old_str = game->str_print;
	str_moves = ft_itoa(game->moves);
	game->str_print = ft_strjoin("Moves: ", str_moves);
	free(old_str);
	free(str_moves);
	mlx_delete_image(game->mlx, game->counter_img);
	game->counter_img = mlx_put_string(game->mlx, game->str_print, 0, 0);
}
