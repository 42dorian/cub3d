/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 13:20:23 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/18 13:11:05 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_last_index_of_map(char **read_file)
{
	int	last_index;

	last_index = get_2d_len(read_file) - 1;
	while (!read_file[last_index][0])
		last_index--;
	return (last_index);
}

const char	**create_texture_set(void)
{
	const char	**texture_set;

	texture_set = ft_calloc(sizeof(const char *), 7);
	if (!texture_set)
		return (NULL);
	texture_set[0] = "NO";
	texture_set[1] = "SO";
	texture_set[2] = "WE";
	texture_set[3] = "EA";
	texture_set[4] = "F";
	texture_set[5] = "C";
	texture_set[6] = NULL;
	return (texture_set);
}

int	find_index_of(char **read_file, const char *word)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(word);
	while (read_file[i])
	{
		if (!ft_strncmp(word, read_file[i], len))
			return (i);
		i++;
	}
	return (-1);
}

int	compare_until_end(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!str1 && str2)
		return (1);
	while ((str1[i] != '\0' && !is_end(str2[i])))
	{
		if (str1[i] != str2[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_in_texture_set(char *line, const char **texture_set)
{
	int			i;
	
	i = 0;
	while (texture_set[i])
	{
		if (!compare_until_end(texture_set[i], line))
			return (1);
		i++;
	}
	return (0);
}

int	multiple_definitions(char **read_file, int last_index)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i < last_index)
	{
		j = i + 1;
		while (j < last_index)
		{
			if (!compare_until_end(read_file[i], read_file[j]))
			{
				write(2, "Error\nMultiple definitons of id(s)!\n", 36);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	only_ids(char **read_file, int *biggest_index, const char **texture_set)
{
	int i;
	
	i = 0;
	while (i < *biggest_index)
	{
		if (!is_in_texture_set(read_file[i], texture_set))
		{
			write(2, "Error\nInvalid identifier!\n", 26);
			return (0);
		}
		i++;
	}
	if (multiple_definitions(read_file, *biggest_index))
		return (0);
	(*biggest_index)++;
	while (!read_file[(*biggest_index)][0])
		(*biggest_index)++;
	return (1);
}

int	get_first_index_of_map(char **read_file)
{
	int			i;
	int			biggest_index;
	const char	**texture_set;

	i = 0;
	biggest_index = 0;
	texture_set = create_texture_set();
	if (!texture_set)
		return (-1);
	while (i < 6)
	{
		if (find_index_of(read_file, texture_set[i]) > biggest_index)
			biggest_index = find_index_of(read_file, texture_set[i]);
		i++;
	}
	if (!only_ids(read_file, &biggest_index, texture_set))
		return (free(texture_set), -1);
	free(texture_set);
	return (biggest_index);
}

int	is_valid_input(char **read_file)
{
	int	first_index;
	int	last_index;

	first_index = get_first_index_of_map(read_file);
	if (first_index == -1)
		return (clean_up_2d(read_file), 0);
	last_index = get_last_index_of_map(read_file);
	while (first_index < last_index)
	{
		if (!(read_file[first_index][0]))
		{
			write(2, "Error\nMultiple maps!\n", 21);
			clean_up_2d(read_file);
			return (0);
		}
		first_index++;
	}
	return (1);
}