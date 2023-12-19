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
	images->exit_close_tex = mlx_load_png("./img/gate_closed_64x64.png");
	if (!images->exit_close_tex)
		error();
	images->exit_close_img = mlx_texture_to_image(mlx, images->exit_close_tex);
	if (!images->exit_close_img)
		error();
	images->exit_open_tex = mlx_load_png("./img/gate_opened_64x64.png");
	if (!images->exit_open_tex)
		error();
	images->exit_open_img = mlx_texture_to_image(mlx, images->exit_open_tex);
	if (!images->exit_open_img)
		error();
	mlx_delete_texture(images->player_tex);
	mlx_delete_texture(images->wall_tex);
	mlx_delete_texture(images->consumable_tex);
	mlx_delete_texture(images->exit_open_tex);
	mlx_delete_texture(images->exit_close_tex);
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
	char	*old_str;
	char	*str_moves;

	game = (t_game*) param;
	x_player = &game->map->x_player;
	y_player = &game->map->y_player;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS && *y_player > 1 && (game->map->array[*y_player - 1][*x_player] != '1'))
	{
		game->images->player_img->instances[0].y -= BLOCK_WIDTH;
		*y_player -= 1;
		game->moves += 1;
		ft_printf("Moves: %d\n", game->moves);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS && *x_player > 1 && (game->map->array[*y_player][*x_player - 1] != '1'))
	{
		game->images->player_img->instances[0].x -= BLOCK_WIDTH;
		*x_player -= 1;
		game->moves += 1;
		ft_printf("Moves: %d\n", game->moves);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS && (*y_player < (game->map->y - 2)) && (game->map->array[*y_player + 1][*x_player] != '1'))
	{
		game->images->player_img->instances[0].y += BLOCK_WIDTH;
		*y_player += 1;
		game->moves += 1;
		ft_printf("Moves: %d\n", game->moves);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS && *x_player < (game->map->x - 2) && (game->map->array[*y_player][*x_player + 1] != '1'))
	{
		game->images->player_img->instances[0].x += BLOCK_WIDTH;
		*x_player += 1;
		game->moves += 1;
		ft_printf("Moves: %d\n", game->moves);
	}
	if (game->map->array[*y_player][*x_player] == 'C')
	{
		ft_putstr_fd("Omnomnom! Lettuce, sweet!\n", 1);
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
			ft_putstr_fd("Everything is collected, exit is open!\n", 1);
			game->images->exit_close_img[0].enabled = 0;
			game->images->exit_open_img[0].enabled = 1;
		}
	}
	if (game->map->exit_open == 1 && game->map->array[*y_player][*x_player] == 'E')
	{
		game->map->array[*y_player][*x_player] = 'e';
		ft_putstr_fd("You won!\n", 1);
		mlx_terminate(game->mlx); 
		free_array(game->map->array);
		free(game->str_print);
		free(game->images);
		exit(0);
	}
	old_str = game->str_print;
	str_moves = ft_itoa(game->moves);
	game->str_print = ft_strjoin("Moves: ", str_moves);
	free(old_str);
	free(str_moves);
	mlx_put_string(game->mlx, game->str_print, 0, 0);
}

int32_t	main(int argc, char **argv)
{
	t_game		*game;
	t_game		game_var;

	game = &game_var;
	if (argc == 2)
		game->map = get_map(argv[1]);
	else
	{
		ft_putstr_fd("Error: Two arguments needed. Format: ./so_long MAP_NAME.ber\n", 2);
		ft_putstr_fd("Try run with: ./so_long map1.ber\n", 1);
		return (1);
	}
	if (!(game->mlx = mlx_init(game->map->x * BLOCK_WIDTH, game->map->y * BLOCK_HEIGHT, "\"The lettuce is soo tasty!\" - The mystic magician", false)))
		return (EXIT_FAILURE);
	ft_printf("try1\n");
	game->images = load_images(game->mlx);
	ft_printf("try2\n");
	ft_printf("%d, %d\n", game->map->x, game->map->y);
	ft_put_sprite(game->mlx, game->images->wall_img, game->map, '1');
	ft_put_sprite(game->mlx, game->images->exit_open_img, game->map, 'E');
	ft_put_sprite(game->mlx, game->images->exit_close_img, game->map, 'E');
	ft_put_sprite(game->mlx, game->images->consumable_img, game->map, 'C');
	// better to put it in some init function?
	game->images->exit_open_img[0].enabled = 0;
	game->map->to_collect = game->images->consumable_img->count; // how many consumables to collect
	game->moves = 0;
	game->str_print = NULL;
	ft_put_sprite(game->mlx, game->images->player_img, game->map, 'P');
	mlx_key_hook(game->mlx, &my_keyhook, (void*) game);
	mlx_loop(game->mlx);
	return (EXIT_SUCCESS);
}
