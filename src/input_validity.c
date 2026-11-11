/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 13:20:23 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/11 15:58:23 by dabdulla         ###   ########.fr       */
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
	biggest_index++;
	while (!read_file[biggest_index][0])
	{
		biggest_index++;
	}
	free(texture_set);
	return (biggest_index);
}

int	is_valid_input(char **read_file)
{
	int	first_index;
	int	last_index;

	last_index = get_last_index_of_map(read_file);
	first_index = get_first_index_of_map(read_file);
	if (first_index == -1)
		return (0);
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
