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

# define WIDTH 1000
# define HEIGHT 800

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
	size_t	i_pos;
	size_t	j_pos;
}			t_map;

// map_check.c
char	**map_check(char *str);

// map_utils.c
char	**map_to_array(int fd);
char	**map_file_to_array(char *map_name);
void	get_P_pos(char **map_array, t_map *map);
void	map_flood_fill(char **map_array, int i, int j);

// utils.c:
int		ft_arrlen(char **arr);
char	**ft_arrdup(char **arr);
int		free_array(char **array);
int		count_char_in_str(char *str, char to_find);
int		count_char_in_arr(char **array, char to_find);

#endif