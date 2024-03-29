/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:00:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/02/13 11:36:19 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

char	**map_to_array(int fd)
{
	char	**map_array;
	char	*one_line;
	char	*lines;
	char	*old_lines;

	old_lines = NULL;
	one_line = get_next_line(fd);
	if (one_line == NULL)
		return (NULL);
	lines = ft_strjoin("", one_line);
	free (one_line);
	while (1)
	{
		one_line = get_next_line(fd);
		if (one_line == NULL)
			break ;
		old_lines = lines;
		lines = ft_strjoin(old_lines, one_line);
		free(old_lines);
		free(one_line);
	}
	map_array = ft_split(lines, '\n');
	free(lines);
	return (map_array);
}

char	**map_file_to_array(char *map_name, t_map *map)
{
	int		fd;
	char	*map_path;
	char	**map_array;

	map_path = ft_strjoin("map/", map_name);
	ft_printf("Looking for map at: %s\n", map_path);
	fd = open(map_path, O_RDONLY, 0444);
	free(map_path);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Map not found. It has to be in map folder.\n", 2);
		free(map);
		exit(1);
	}
	else
		ft_putstr_fd("Map found!\n", 1);
	map_array = map_to_array(fd);
	if (map_array == NULL)
	{
		ft_putstr_fd("Error: Map file empty\n", 2);
		free(map);
		exit(2);
	}
	return (map_array);
}

void	get_player_pos(char **map_array, t_map *map)
{
	size_t	y;
	size_t	x;

	map->x_player = 0;
	map->y_player = 0;
	y = 0;
	while (map_array[y])
	{
		x = 0;
		while (map_array[y][x])
		{
			if (map_array[y][x] == 'P')
			{
				map->x_player = x;
				map->y_player = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	map_flood_fill(char **map_array, size_t y, size_t x)
{
	if (map_array[y][x] == 'c' || map_array[y][x] == 'e'
		|| map_array[y][x] == 'p' || map_array[y][x] == '1'
		|| map_array[y][x] == '2' || map_array[y][x] == 'B')
		return ;
	if (map_array[y][x] == 'C')
		map_array[y][x] = 'c';
	else if (map_array[y][x] == 'P')
		map_array[y][x] = 'p';
	else if (map_array[y][x] == 'E')
		map_array[y][x] = 'e';
	else if (map_array[y][x] == '0')
		map_array[y][x] = '2';
	map_flood_fill(map_array, y + 1, x);
	map_flood_fill(map_array, y - 1, x);
	map_flood_fill(map_array, y, x + 1);
	map_flood_fill(map_array, y, x - 1);
}
