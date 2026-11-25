/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 19:27:38 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/20 19:28:48 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*creating_t_cub_struct(char **read_file)
{
	t_map	*map_struct;

	map_struct = ft_calloc(sizeof(t_map), 1);
	if (!map_struct)
		return (NULL);
	if (!trim_the_read_file(read_file))
		return (t_map_clean_up(map_struct), NULL);
	if (!is_valid_input(read_file))
		return (t_map_clean_up(map_struct), NULL);
	read_file = trim_empty_lines(read_file);
	if (!read_file)
		return (t_map_clean_up(map_struct), NULL);
	if (!get_struct_values(map_struct, read_file))
		return (clean_up_2d(read_file), NULL);
	clean_up_2d(read_file);
	return (map_struct);
}

int	check_missing_textures(t_map *map_struct)
{
	if (!ft_strncmp(map_struct->ea, "", 1))
		return (print_missing_id_error("EA"), 1);
	if (!ft_strncmp(map_struct->we, "", 1))
		return (print_missing_id_error("WE"), 1);
	if (!ft_strncmp(map_struct->no, "", 1))
		return (print_missing_id_error("NO"), 1);
	if (!ft_strncmp(map_struct->so, "", 1))
		return (print_missing_id_error("SO"), 1);
	return (0);
}

int	add_colours_to_array(int *colours, char **split_colours)
{
	int	i;

	i = 0;
	while (split_colours[i])
	{
		colours[i] = ft_atoi(split_colours[i]);
		if (colours[i] == -1 || colours[i] == -2)
		{
			print_colour_code_error();
			free(colours);
			colours = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

int	allocate_colours_and_split_line(int **colours, char ***split_line,
		char *line)
{
	*colours = ft_calloc(sizeof(int), 4);
	if (!*colours)
		return (0);
	*split_line = ft_split(line, SPACE);
	if (!*split_line)
		return (free(*colours), 0);
	if (get_2d_len(*split_line) == 1)
	{
		print_missing_texture_pack(*split_line[0]);
		clean_up_2d(*split_line);
		free(*colours);
		return (0);
	}
	else if (get_2d_len(*split_line) > 2)
	{
		print_multiple_texture_packs(*split_line[0]);
		clean_up_2d(*split_line);
		free(*colours);
		return (0);
	}
	return (1);
}

char	**get_map(char **read_file)
{
	char	**map;
	int		last_index;
	int		full_len;
	int		curr_len;

	full_len = get_map_len_from_file(read_file);
	last_index = get_2d_len(read_file) - 1;
	map = ft_calloc(sizeof(char *), full_len + 1);
	if (!map)
		return (NULL);
	curr_len = full_len;
	map[curr_len--] = NULL;
	while (curr_len >= 0)
	{
		map[curr_len] = normal_copy(read_file[last_index]);
		if (!map[curr_len])
			return (free_map_with_index(map, full_len, curr_len), NULL);
		curr_len--;
		last_index--;
	}
	return (map);
}
