/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:16:23 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/04 12:59:44 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	is_consumable(t_game *game, size_t y_player, size_t x_player)
{
	size_t	i;
	size_t	img_x;
	size_t	img_y;

	i = 0;
	if (game->map->array[y_player][x_player] == 'C')
	{
		game->map->array[y_player][x_player] = 'c';
		while (i < game->images->consum_img->count)
		{
			img_x = (size_t) game->images->consum_img->instances[i].x;
			img_y = (size_t) game->images->consum_img->instances[i].y;
			if (img_x / BLOCK_W == x_player && img_y / BLOCK_H == y_player)
				game->images->consum_img->instances[i].enabled = 0;
			i++;
		}
		game->map->to_collect -= 1;
		if (game->map->to_collect == 0)
		{
			game->map->exit_open = 1;
			game->images->ex_cls_img[0].enabled = 0;
			game->images->ex_opn_img[0].enabled = 1;
		}
	}
}

void	is_enemy(t_game *game, size_t y_player, size_t x_player)
{
	if (game->map->array[y_player][x_player] == 'B')
	{
		ft_putstr_fd("||  GAME OVER   ||\n|| YOU ARE DEAD ||\n", 1);
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
		free_array(game->map->array);
		free(game->str_print);
		free(game->images);
		exit(0);
	}
}

void	is_exit(t_game *game, size_t y_player, size_t x_player)
{
	if (game->map->exit_open == 1
		&& game->map->array[y_player][x_player] == 'E')
	{
		ft_printf("||          You won!         ||\n", game->moves);
		ft_printf("|| Final number of moves: %d ||\n", game->moves);
		game_clean(game);
		exit(0);
	}
}
