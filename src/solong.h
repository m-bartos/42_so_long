/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:27:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/04 12:57:18 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# define BLOCK_W 64
# define BLOCK_H 64

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>

typedef struct map
{
	char	**array;
	size_t	x;
	size_t	y;
	size_t	x_player;
	size_t	y_player;
	size_t	to_collect;
	size_t	exit_open;
}			t_map;

typedef struct images
{
	mlx_texture_t	*ex_opn_tex;
	mlx_image_t		*ex_opn_img;
	mlx_texture_t	*ex_cls_tex;
	mlx_image_t		*ex_cls_img;
	mlx_texture_t	*consum_tex;
	mlx_image_t		*consum_img;
	mlx_texture_t	*player_tex;
	mlx_image_t		*player_img;
	mlx_texture_t	*wall_tex;
	mlx_image_t		*wall_img;
	mlx_texture_t	*enemy_tex;
	mlx_image_t		*enemy_img;
}			t_images;

typedef struct game
{
	mlx_t		*mlx;
	t_map		*map;
	t_images	*images;
	size_t		moves;
	char		*str_print;
	mlx_image_t	*counter_img;
}			t_game;

// errors.c
void		error(void);
void		error_argc(int argc);
void		error_map_open(void);

// hook_utils.c
void		is_consumable(t_game *game, size_t y_player, size_t x_player);
void		is_enemy(t_game *game, size_t y_player, size_t x_player);
void		is_exit(t_game *game, size_t y_player, size_t x_player);

// hook.c
void		is_esc_pressed(mlx_key_data_t keydata, t_game *game);
void		move_player_x(t_game *game, size_t *x_player, int x);
void		move_player_y(t_game *game, size_t *y_player, int y);
void		is_wsad_pressed(mlx_key_data_t keydata, t_game *game,
				size_t *y_player, size_t *x_player);
void		keyhook(mlx_key_data_t keydata, void *param);

// images.c
void		img_and_tex(char *path, mlx_t *mlx,
				mlx_texture_t **tex, mlx_image_t **img);
t_images	*load_images(mlx_t *mlx);
void		ft_put_sprite(mlx_t *mlx, mlx_image_t *img,
				t_map *map, char symbol);
void		put_score(t_game *game);

// map_check.c

/**
 * Checks the validity of a map file.
 * 
 * Description:
 * @note Checks if the map file has the correct suffix (*.bek).
 * @note Validates that the map is rectangular.
 * @note Verifies that the map is closed (borders are present).
 * @note Ensures there is a valid path (all collectibles and exit are reachable).
 * @note Validates the correct num of collectibles, exit, player start position.
 * 
 * @param str The name of the map file to be checked.
 *            Assumed to have the correct suffix (*.bek).
 * 
 * @return map as an array of char*
 */
t_map		*get_map(char *str);

// map_check_utils.c
char		**map_to_array(int fd);
char		**map_file_to_array(char *map_name);
void		get_player_pos(char **map_array, t_map *map);
void		map_flood_fill(char **map_array, size_t y, size_t x);

// so_long.c
void		game_clean(t_game *game);

// utils.c:

/**
 * Calculates the length of a null-terminated array of strings.
 * 
 * @param arr Pointer to a null-terminated array of strings.
 * 
 * Description:
 * - Counts the number of strings in the array until encountering a NULL pointer.
 * 
 * @return The number of strings in the array.
 */
int			ft_arrlen(char **arr);
char		**ft_arrdup(char **arr);
int			free_array(char **array);
int			count_char_in_str(char *str, char to_find);
int			nof_char_in_arr(char **array, char to_find);

#endif