/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:10:44 by mbartos           #+#    #+#             */
/*   Updated: 2023/12/22 11:43:19 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	game_init(t_game *game)
{
	game->images->ex_opn_img[0].enabled = 0;
	game->map->to_collect = game->images->consum_img->count;
	game->moves = 0;
	game->str_print = ft_strjoin("Moves: ", "0");
	game->counter_img = mlx_put_string(game->mlx, game->str_print, 0, 0);
	ft_printf("Moves: %d\n", game->moves);
}

int32_t	main(int argc, char **argv)
{
	t_game	*game;
	t_game	game_var;
	int32_t	width;
	int32_t	height;

	game = &game_var;
	error_argc(argc);
	game->map = get_map(argv[1]);
	width = game->map->x * BLOCK_W;
	height = game->map->y * BLOCK_H;
	game->mlx = mlx_init(width, height, "So_long - The lettuce Magican", false);
	if (!game->mlx)
		return (EXIT_FAILURE);
	game->images = load_images(game->mlx);
	ft_put_sprite(game->mlx, game->images->wall_img, game->map, '1');
	ft_put_sprite(game->mlx, game->images->ex_opn_img, game->map, 'E');
	ft_put_sprite(game->mlx, game->images->ex_cls_img, game->map, 'E');
	ft_put_sprite(game->mlx, game->images->consum_img, game->map, 'C');
	ft_put_sprite(game->mlx, game->images->enemy_img, game->map, 'B');
	ft_put_sprite(game->mlx, game->images->player_img, game->map, 'P');
	game_init(game);
	mlx_key_hook(game->mlx, &keyhook, (void *) game);
	mlx_loop(game->mlx);
	return (EXIT_SUCCESS);
}
