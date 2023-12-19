/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:15:19 by mbartos           #+#    #+#             */
/*   Updated: 2023/12/15 14:15:21 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

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
int	ft_arrlen(char **arr)
{
	int	len;

	len = 0;
	while(*arr++)
		len++;
	return (len);
}

char	**ft_arrdup(char **arr)
{
	size_t	i;
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
	new_arr[i] = NULL;
	return (new_arr);
}

int	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (*(array + i))
	{
		free(*(array + i));
		i++;
	}
	free(array);
	return (1);
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

int	nof_char_in_arr(char **array, char to_find)
{
	int	total_count;

	total_count = 0;
	while (*array)
		total_count = total_count + count_char_in_str(*array++, to_find);
	return(total_count);
}