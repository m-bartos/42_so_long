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

//checking the ending *.ber of string
void	suffix_check(char *str)
{
	char	*suf;
	size_t	str_len;
	size_t	suf_len;
	size_t	i;

	suf = ft_strdup(".bek");
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
			ft_putstr_fd("Error: invalid name of map file, *.bek suffix missing\n", 2);
			free(suf);
			exit (1);
		}
	}
	free(suf);
}

char	**map_to_array(int fd)
{
	char	*one_line;
	char	*lines;
	char	*old_lines;

	old_lines = NULL;
	one_line = get_next_line(fd);
	if (one_line == NULL)
		return (NULL);
	lines = ft_strjoin("", one_line);
	while (1)
	{
		one_line = get_next_line(fd);
		if (one_line == NULL)
			break;
		old_lines = lines;
		lines = ft_strjoin(old_lines, one_line);
		free(old_lines);
		free(one_line);
	}
	return (ft_split(lines, '\n'));
}

char	**map_file_to_array(char *map_name)
{
	int		fd;
	char	*map_path;
	char	**map_array;

	map_path = ft_strjoin("map/", map_name);
	ft_printf("Looking for map at: %s\n", map_path); //not necessary, just info
	fd = open(map_path, O_RDONLY, 0444);
	free(map_path);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Map not found. It has to be located in map folder.\n", 2);
		exit (1);
	}
	else
		ft_putstr_fd("Map found!\n", 1); //not necessary, just info
	map_array = map_to_array(fd);
	if (map_array == NULL)
	{
		ft_putstr_fd("Error: Map file empty\n", 2);
		exit(1);
	}
	return (map_array);
}

int	count_char_in_str(char *str, char to_find)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == to_find)
			count++;
		str++;
	}
	return (count);
}

int	count_char_in_arr(char **array, char to_find)
{
	int	i;
	int	total_count;

	i = 0;
	total_count = 0;
	while (*array)
		total_count = total_count + count_char_in_str(*array++, to_find);
	return(total_count);
}

void	n_PEC_check(char **map_array, char **map_flooded)
{
	if (count_char_in_arr(map_array, 'E') == 1 && count_char_in_arr(map_flooded, 'e'))
		ft_putstr_fd("Correct number of exits\n", 1); //not necessary, just info
	else
	{
		ft_putstr_fd("Error: Incorrect number of rechable exits!\n", 2);
		exit(1);
	}
	if (count_char_in_arr(map_array, 'P') == 1 && count_char_in_arr(map_flooded, 'p'))
		ft_putstr_fd("Correct number of starts\n", 1); //not necessary, just info
	else
	{
		ft_putstr_fd("Error: Incorrect number of rechable starts!\n", 2);
		exit(1);
	}
	if (count_char_in_arr(map_array, 'C') >= 1 && count_char_in_arr(map_array, 'C') == count_char_in_arr(map_flooded, 'c'))
		ft_putstr_fd("Correct number of collectibles\n", 1); //not necessary, just info
	else
	{
		ft_putstr_fd("Error: Incorrect number of rechable collectibles!\n", 2);
		exit(1);
	}
}

void	rectang_map_check(char **map_array)
{
	int	i;

	i = 0;
	while (map_array[i])
	{
		i++;
	}
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

void	closed_map_check(char **map_array)
{
	size_t	i;
	size_t	j;

	i = 0;
	while(map_array[i])
	{
		if(i == 0 || map_array[i + 1] == NULL)
		{
			j = 0;
			while (map_array[i][j])
			{
				if (map_array[i][j] != '1')
				{
					ft_putstr_fd("Error: Map is not closed with '1'.\n", 2);
					exit (1);
				}
				j++;
			}
		}
		else
		{
			if (map_array[i][0] != '1' | map_array[i][ft_strlen(map_array[i]) - 1] != '1')
			{
				ft_putstr_fd("Error: Map is not closed with '1'.\n", 2);
				exit (1);
			}
		}
		i++;
	}
	ft_putstr_fd("Map is correctly closed with '1'.\n", 1);
}

int	ft_arrlen(char **arr)
{
	int	len;

	len = 0;
	while(*arr++)
		len++;
	return (len);
}

void	P_pos(char **map_array, t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map_array[i])
	{
		j = 0;
		while(map_array[i][j])
		{
			if (map_array[i][j] == 'P')
			{
				map->i_pos = i;
				map->j_pos = j;
				return;
			}
			j++;
		}
		i++;
	}
}

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**new_arr;

	new_arr = (char **) malloc((ft_arrlen(arr) + 1) * sizeof(char*));
	if (new_arr == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] == NULL;
	return (new_arr);
}

void	flood_fill(char **map_array, int i, int j)
{
	if (map_array[i][j] == 'c' || map_array[i][j] == 'e' || map_array[i][j] == 'p' || map_array[i][j] == '1' || map_array[i][j] == '2')
		return ;
	if (map_array[i][j] == 'C')
		map_array[i][j] = 'c';
	else if (map_array[i][j] == 'P')
		map_array[i][j] = 'p';
	else if (map_array[i][j] == 'E')
		map_array[i][j] = 'e';
	else if (map_array[i][j] == '0')
		map_array[i][j] = '2';
	flood_fill(map_array, i + 1, j);
	flood_fill(map_array, i - 1, j);
	flood_fill(map_array, i, j + 1);
	flood_fill(map_array, i, j - 1);
}

int	map_check(char *str)
{
	t_map	map;
	char	**map_array;
	char	**map_flooded;
	size_t	i;

	ft_putstr_fd("------------------\n", 1);
	ft_putstr_fd("Map check:\n", 1);
	// main function of map_check - return value = array of strings
	// checking the suffix
	suffix_check(str);
	//getting map from file to array (also checking that the file is present in map folder)
	map_array = map_file_to_array(str);

	// redundant - just showing the map
	ft_printf("\n");
	i = 0;
	while (map_array[i] != NULL)
	{
		ft_printf("%s\n", map_array[i]);
		i++;
	}
	ft_printf("\n");
	// checking the map is rectangular and has more than 3 lines
	rectang_map_check(map_array);
	// checking the map is closed (1 at the borders)
	closed_map_check(map_array);
	// possition of P - player
	P_pos(map_array, &map);
	ft_putnbr_fd(map.i_pos, 1);
	ft_putstr_fd("\n", 1);
	ft_putnbr_fd(map.j_pos, 1);
	ft_putstr_fd("\n", 1);
	// checking if it is possible to reach all the consumable and end from start - flood algorithm
	map_flooded = ft_arrdup(map_array);
	flood_fill(map_flooded, map.i_pos, map.j_pos);
	ft_printf("\n");
	i = 0;
	while (map_flooded[i] != NULL)
	{
		ft_printf("%s\n", map_flooded[i]);
		i++;
	}
	// check the number of player positions P == 1, exists == 1 and collectibles >= 1
	n_PEC_check(map_array, map_flooded);
	ft_printf("\n");
	ft_putstr_fd("------------------\n", 1);
}