/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:27:47 by mbartos           #+#    #+#             */
/*   Updated: 2023/12/12 13:15:24 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# define BLOCK_WIDTH 64
# define BLOCK_HEIGHT 64

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
//# include <sys/wait.h>
//# include <X11/X.h>
//# include <X11/keysym.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>

typedef struct	map {
	char	**array;
	size_t	x;
	size_t	y;
	size_t	x_player;
	size_t	y_player;
	size_t	to_collect;
	size_t	exit_open;
}			t_map;

typedef struct	images {
	mlx_texture_t	*exit_open_tex;
	mlx_image_t		*exit_open_img;
	mlx_texture_t	*exit_close_tex;
	mlx_image_t		*exit_close_img;
	mlx_texture_t	*consumable_tex;
	mlx_image_t		*consumable_img;
	mlx_texture_t	*player_tex;
	mlx_image_t		*player_img;
	mlx_texture_t	*wall_tex;
	mlx_image_t		*wall_img;
}			t_images;

typedef struct	game {
	mlx_t		*mlx;
	t_map		*map;
	t_images	*images;
	size_t		moves;
	char		*str_print;
	mlx_image_t	*counter_img;
}			t_game;

// map_check.c
t_map	*get_map(char *str);

// map_utils.c
char	**map_to_array(int fd);
char	**map_file_to_array(char *map_name);
void	get_P_pos(char **map_array, t_map *map);
void	map_flood_fill(char **map_array, size_t y, size_t x);

// utils.c:
int		ft_arrlen(char **arr);
char	**ft_arrdup(char **arr);
int		free_array(char **array);
int		count_char_in_str(char *str, char to_find);
int		count_char_in_arr(char **array, char to_find);

#endif