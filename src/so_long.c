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

static void error(void)
{
	ft_putstr_fd((char *) mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}

t_images	*load_images(mlx_t *mlx)
{
	t_images	*images;

	images = (t_images *) malloc(1 * sizeof(t_images));
	if (!images)
		error();
	images->player_tex = mlx_load_png("./img/Wizard_Man_64x64.png");
	if (!images->player_tex)
		error();
	images->player_img = mlx_texture_to_image(mlx, images->player_tex);
	if (!images->player_img)
		error();
	images->wall_tex = mlx_load_png("./img/Wall_64x64.png");
	if (!images->wall_tex)
		error();
	images->wall_img = mlx_texture_to_image(mlx, images->wall_tex);
	if (!images->wall_img)
		error();
	images->consumable_tex = mlx_load_png("./img/Consumable_64x64.png");
	if (!images->consumable_tex)
		error();
	images->consumable_img = mlx_texture_to_image(mlx, images->consumable_tex);
	if (!images->consumable_img)
		error();
	images->exit_tex = mlx_load_png("./img/gate_closed_64x64.png");
	if (!images->exit_tex)
		error();
	images->exit_img = mlx_texture_to_image(mlx, images->exit_tex);
	if (!images->exit_img)
		error();
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
				if (mlx_image_to_window(mlx, img, x * BLOCK_WIDTH, y * BLOCK_HEIGHT) < 0)
					error();
			}
			x++;
		}
		y++;
	}
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_game *game;
	size_t	*x_player;
	size_t	*y_player;

	game = (t_game*) param;
	x_player = &game->map->x_player;
	y_player = &game->map->y_player;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && *y_player > 1 && (game->map->array[*y_player - 1][*x_player] != '1'))
	{
		game->images->player_img->instances[0].y -= BLOCK_WIDTH;
		*y_player -= 1;
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && *x_player > 1 && (game->map->array[*y_player][*x_player - 1] != '1'))
	{
		game->images->player_img->instances[0].x -= BLOCK_WIDTH;
		*x_player -= 1;
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && (*y_player < (game->map->y - 2)) && (game->map->array[*y_player + 1][*x_player] != '1'))
	{
		game->images->player_img->instances[0].y += BLOCK_WIDTH;
		*y_player += 1;
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && *x_player < (game->map->x - 2) && (game->map->array[*y_player][*x_player + 1] != '1'))
	{
		game->images->player_img->instances[0].x += BLOCK_WIDTH;
		*x_player += 1;
	}
	if (game->map->array[*y_player][*x_player] == 'C')
	{
		ft_putstr_fd("You have collected one consumable.\n", 1);
		game->map->array[*y_player][*x_player] = 'c';
		size_t	i;
		i = 0;
		while (i < game->images->consumable_img->count)
		{
			if ((size_t) game->images->consumable_img->instances[i].x/BLOCK_WIDTH == *x_player && (size_t) game->images->consumable_img->instances[i].y/BLOCK_HEIGHT == *y_player)
				game->images->consumable_img->instances[i].enabled = 0;
			i++;
		}
		game->map->to_collect -= 1;
		if (game->map->to_collect == 0)
		{
			game->map->exit_open = 1;
			ft_putstr_fd("Everything is collected! Go to exit\n", 1);
			mlx_delete_image(game->mlx, game->images->exit_img);
			game->images->exit_tex = mlx_load_png("./img/gate_opened_64x64.png");
			if (!game->images->exit_tex)
				error();
			game->images->exit_img = mlx_texture_to_image(game->mlx, game->images->exit_tex);
			if (!game->images->exit_img)
				error();
			ft_put_sprite(game->mlx, game->images->exit_img, game->map, 'E');
		}
	}
	if (game->map->exit_open == 1 && game->map->array[*y_player][*x_player] == 'E')
	{
		game->map->array[*y_player][*x_player] = 'e';
		ft_putstr_fd("You won!\n", 1);
		free_array(game->map->array); //freeing needs to be better
		free(game->map);
		mlx_terminate(game->mlx); //got segfault
	}
}

int32_t	main(int argc, char **argv)
{
	t_game		*game;

	game = (t_game*) malloc(1 * sizeof(t_game));
	if (argc == 2)
		game->map = get_map(argv[1]);
	else
	{
		ft_putstr_fd("Error: Two arguments needed. Format: ./so_long MAP_NAME.ber\n", 2);
		ft_putstr_fd("Try run with: ./so_long map1.ber\n", 1);
		return (1);
	}
	if (!(game->mlx = mlx_init(game->map->x * BLOCK_WIDTH, game->map->y * BLOCK_HEIGHT, "So long - The mystic magician", true)))
		return (EXIT_FAILURE);
	game->images = load_images(game->mlx);
	ft_put_sprite(game->mlx, game->images->wall_img, game->map, '1');
	ft_put_sprite(game->mlx, game->images->exit_img, game->map, 'E');
	ft_put_sprite(game->mlx, game->images->consumable_img, game->map, 'C');
	game->map->to_collect = game->images->consumable_img->count; // how many consumables to collect
	ft_put_sprite(game->mlx, game->images->player_img, game->map, 'P');
	mlx_key_hook(game->mlx, &my_keyhook, (void*) game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}
