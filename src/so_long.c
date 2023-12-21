/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:10:44 by mbartos           #+#    #+#             */
/*   Updated: 2023/12/12 17:40:13 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	error(void)
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

void	is_consumable(t_game *game, size_t y_player, size_t x_player)
{
	size_t	i;
	size_t	img_x;
	size_t	img_y;

	i = 0;
	if (game->map->array[y_player][x_player] == 'C')
	{
		game->map->array[y_player][x_player] = 'c';
		while (i < game->images->consumable_img->count)
		{
			img_x = (size_t) game->images->consumable_img->instances[i].x;
			img_y = (size_t) game->images->consumable_img->instances[i].y;
			if (img_x / BLOCK_W == x_player && img_y / BLOCK_H == y_player)
				game->images->consumable_img->instances[i].enabled = 0;
			i++;
		}
		game->map->to_collect -= 1;
		if (game->map->to_collect == 0)
		{
			game->map->exit_open = 1;
			game->images->exit_close_img[0].enabled = 0;
			game->images->exit_open_img[0].enabled = 1;
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
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
		free_array(game->map->array);
		free(game->str_print);
		free(game->images);
		exit(0);
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

void	is_wsad_pressed(mlx_key_data_t keydata, t_game *game,
						size_t *y_player, size_t *x_player)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS
		&& *y_player > 1 && (game->map->array[*y_player - 1][*x_player] != '1'))
	{
		game->images->player_img->instances[0].y -= BLOCK_H;
		*y_player -= 1;
	}
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS
		&& *x_player > 1 && (game->map->array[*y_player][*x_player - 1] != '1'))
	{
		game->images->player_img->instances[0].x -= BLOCK_W;
		*x_player -= 1;
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS
		&& (*y_player < (game->map->y - 2))
		&& (game->map->array[*y_player + 1][*x_player] != '1'))
	{
		game->images->player_img->instances[0].y += BLOCK_H;
		*y_player += 1;
	}
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS
		&& *x_player < (game->map->x - 2)
		&& (game->map->array[*y_player][*x_player + 1] != '1'))
	{
		game->images->player_img->instances[0].x += BLOCK_W;
		*x_player += 1;
	}
	else
		return ;
	game->moves += 1;
	ft_printf("Moves: %d\n", game->moves);
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

void	game_init(t_game *game)
{
	game->images->exit_open_img[0].enabled = 0;
	game->map->to_collect = game->images->consumable_img->count;
	game->moves = 0;
	game->str_print = ft_strjoin("Moves: ", "0");
	game->counter_img = mlx_put_string(game->mlx, game->str_print, 0, 0);
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
	ft_put_sprite(game->mlx, game->images->exit_open_img, game->map, 'E');
	ft_put_sprite(game->mlx, game->images->exit_close_img, game->map, 'E');
	ft_put_sprite(game->mlx, game->images->consumable_img, game->map, 'C');
	ft_put_sprite(game->mlx, game->images->enemy_img, game->map, 'B');
	ft_put_sprite(game->mlx, game->images->player_img, game->map, 'P');
	game_init(game);
	mlx_key_hook(game->mlx, &keyhook, (void *) game);
	mlx_loop(game->mlx);
	return (EXIT_SUCCESS);
}
