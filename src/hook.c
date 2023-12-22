/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:43:00 by mbartos           #+#    #+#             */
/*   Updated: 2023/12/22 11:44:40 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	is_esc_pressed(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
		free_array(game->map->array);
		free(game->str_print);
		free(game->images);
		ft_printf("|| You have left the game ||\n");
		exit(0);
	}
}

void	move_player_x(t_game *game, size_t *x_player, int x)
{
	game->images->player_img->instances[0].x += x * BLOCK_W;
	*x_player += x;
	game->moves += 1;
	ft_printf("Moves: %d\n", game->moves);
}

void	move_player_y(t_game *game, size_t *y_player, int y)
{
	game->images->player_img->instances[0].y += y * BLOCK_W;
	*y_player += y;
	game->moves += 1;
	ft_printf("Moves: %d\n", game->moves);
}

void	is_wsad_pressed(mlx_key_data_t keydata, t_game *game,
						size_t *y_player, size_t *x_player)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS
		&& *y_player > 1 && (game->map->array[*y_player - 1][*x_player] != '1'))
	{
		move_player_y(game, y_player, -1);
	}
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS
		&& *x_player > 1 && (game->map->array[*y_player][*x_player - 1] != '1'))
	{
		move_player_x(game, x_player, -1);
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS
		&& (*y_player < (game->map->y - 2))
		&& (game->map->array[*y_player + 1][*x_player] != '1'))
	{
		move_player_y(game, y_player, +1);
	}
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS
		&& *x_player < (game->map->x - 2)
		&& (game->map->array[*y_player][*x_player + 1] != '1'))
	{
		move_player_x(game, x_player, +1);
	}
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	size_t	*x_player;
	size_t	*y_player;

	game = (t_game *) param;
	x_player = &game->map->x_player;
	y_player = &game->map->y_player;
	is_esc_pressed(keydata, game);
	is_wsad_pressed(keydata, game, y_player, x_player);
	is_consumable(game, *y_player, *x_player);
	is_enemy(game, *y_player, *x_player);
	is_exit(game, *y_player, *x_player);
	put_score(game);
}
