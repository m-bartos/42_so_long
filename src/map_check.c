/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:34:42 by mbartos           #+#    #+#             */
/*   Updated: 2023/12/13 15:55:11 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

/**
 * Checks the suffix of a string to validate if it matches a specific pattern.
 * 
 * Description:
 * Generates the expected suffix ".bek".
 * Compares the suffix with the end of the input string to ensure a match.
 * Prints an error message and terminates the program if the suffix is missing.
 * 
 * @param str The string to be checked for the correct suffix (*.bek).
 * 
 * @note This function assumes a specific suffix format (*.bek) for validation.
 * @note Uses ft_strdup, ft_strlen, ft_putstr_fd, free, and exit functions.
 * @note Assumes an error message is printed to stderr (file descriptor 2).
 * @note Exits the program with an error code 1 on suffix mismatch.
 * @note Frees memory allocated for the suffix.
 * @note Does not return a value.
 */
void	check_suffix(char *str)
{
	char	*suf;
	size_t	str_len;
	size_t	suf_len;
	size_t	i;

	suf = ft_strdup(".ber");
	str_len = ft_strlen(str);
	suf_len = ft_strlen(suf);
	i = 0;
	while (suf_len > 0)
	{
		if (str[str_len - suf_len] == suf[i])
		{
			suf_len--;
			i++;
		}
		else
		{
			ft_putstr_fd("Error: invalid map name, *.ber suffix missing\n", 2);
			free(suf);
			exit (1);
		}
	}
	free(suf);
}

void	check_of_pec(char **map_array, char **map_flooded)
{
	if (nof_char_in_arr(map_array, 'E') == 1
		&& nof_char_in_arr(map_flooded, 'e'))
		ft_putstr_fd("Correct number of exits\n", 1);
	else
	{
		ft_putstr_fd("Error: Incorrect number of rechable exits!\n", 2);
		exit(1);
	}
	if (nof_char_in_arr(map_array, 'P') == 1
		&& nof_char_in_arr(map_flooded, 'p'))
		ft_putstr_fd("Correct number of starts\n", 1);
	else
	{
		ft_putstr_fd("Error: Incorrect number of rechable starts!\n", 2);
		exit(1);
	}
	if (nof_char_in_arr(map_array, 'C') >= 1
		&& nof_char_in_arr(map_array, 'C') == nof_char_in_arr(map_flooded, 'c'))
		ft_putstr_fd("Correct number of collectibles\n", 1);
	else
	{
		ft_putstr_fd("Error: Incorrect number of rechable collectibles!\n", 2);
		exit(1);
	}
}

void	check_rectang_map(char **map_array)
{
	size_t	i;

	i = 0;
	while (map_array[i])
		i++;
	if (!(i >= 3))
	{
		ft_putstr_fd("Error: Not enough of map lines (must be >3).\n", 2);
		exit(1);
	}
	i = 1;
	while (map_array[i])
	{
		if (ft_strlen(map_array[0]) != ft_strlen(map_array[i]))
		{
			ft_putstr_fd("Error: Map is not rectangular.\n", 2);
			exit(1);
		}
		i++;
	}
	ft_putstr_fd("Map is correctly rectangular.\n", 1);
}

void	check_closed_map(char **map_array)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (map_array[y])
	{
		if (y == 0 || map_array[y + 1] == NULL)
		{
			x = 0;
			while (map_array[y][x])
			{
				if (map_array[y][x] != '1')
				{
					ft_putstr_fd("Error: Map is not closed.\n", 2);
					exit (1);
				}
				x++;
			}
		}
		else
		{
			if (map_array[y][0] != '1'
				|| map_array[y][ft_strlen(map_array[y]) - 1] != '1')
			{
				ft_putstr_fd("Error: Map is not closed.\n", 2);
				exit (1);
			}
		}
		y++;
	}
	ft_putstr_fd("Map is correctly closed with '1'.\n", 1);
}

t_map	*get_map(char *str)
{
	t_map	*map;
	char	**map_array;
	char	**map_flooded;

	map = (t_map *) malloc(sizeof(t_map) * 1);
	ft_putstr_fd("-------------------\n", 1);
	ft_putstr_fd("-RUNNING_MAP_CHECK-\n", 1);
	ft_putstr_fd("-------------------\n", 1);
	check_suffix(str);
	map_array = map_file_to_array(str);
	check_rectang_map(map_array);
	check_closed_map(map_array);
	get_player_pos(map_array, map);
	map_flooded = ft_arrdup(map_array);
	map_flood_fill(map_flooded, map->y_player, map->x_player);
	check_of_pec(map_array, map_flooded);
	ft_putstr_fd("-------------------\n", 1);
	ft_putstr_fd("---MAP_CHECK_OK----\n", 1);
	ft_putstr_fd("-------------------\n\n", 1);
	map->array = map_array;
	map->x = ft_strlen(map->array[0]);
	map->y = ft_arrlen(map->array);
	map->exit_open = 0;
	free_array(map_flooded);
	return (map);
}
