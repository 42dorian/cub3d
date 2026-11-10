/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_struct_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 12:29:08 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/10 23:51:49 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_struct_values(t_map *map_struct, char **read_file)
{
	map_struct->EA = get_direction(read_file, "EA");
	if (!map_struct->EA)
		return (0);
	map_struct->NO = get_direction(read_file, "NO");
	if (!map_struct->NO)
		return (t_map_clean_up(map_struct), 0);
	map_struct->WE = get_direction(read_file, "WE");
	if (!map_struct->WE)
		return (t_map_clean_up(map_struct), 0);
	map_struct->SO = get_direction(read_file, "SO");
	if (!map_struct->SO)
		return (t_map_clean_up(map_struct), 0);
	map_struct->floor = get_levels(read_file, 'F');
	if (!map_struct->floor)
		return (t_map_clean_up(map_struct), 0);
	map_struct->ceiling = get_levels(read_file, 'C');
	if (!map_struct->ceiling)
		return (t_map_clean_up(map_struct), 0);
	map_struct->map = get_map(read_file);
	if (!map_struct->map)
		return (t_map_clean_up(map_struct), 0);
	if (check_missing_textures(map_struct))
		return (t_map_clean_up(map_struct), 0);
	return (1);
}

int	*get_levels(char **read_file, const char letter)
{
	int	i;

	i = 0;
	while (read_file[i])
	{
		if (matching_levels(read_file[i], letter))
			return (get_colour(read_file[i]));
		i++;
	}
	print_missing_level_id(letter);
	return (NULL);
}

int	*get_colour(char *line)
{
	int		*colours;
	char	**split_line;
	char	**split_colours;

	colours = NULL;
	split_line = NULL;
	if (!allocate_colours_and_split_line(&colours, &split_line, line))
		return (NULL);
	split_colours = ft_split(split_line[1], COMMA);
	if (!split_colours)
		return (clean_up_2d(split_line), free(colours), NULL);
	clean_up_2d(split_line);
	if (!add_colours_to_array(colours, split_colours))
        return (clean_up_2d(split_colours), NULL);
	clean_up_2d(split_colours);
	return (colours);
}

char	*get_direction(char **read_file, const char *direction)
{
	int	i;

	i = 0;
	while (read_file[i])
	{
		if (matching_names(read_file[i], (char *)direction))
			return (get_texture(read_file[i]));
		i++;
	}
	return (ft_strdup(""));
}

char	*get_texture(char *line)
{
	char	*texture_path;
	char	**split_line;

	split_line = ft_split(line, SPACE);
	if (!split_line)
		return (NULL);
	if (get_2d_len(split_line) == 1)
	{
		print_missing_texture_pack(split_line[0]);
		clean_up_2d(split_line);
		return (NULL);
	}
	else if (get_2d_len(split_line) > 2)
	{
		print_multiple_texture_packs(split_line[0]);
		clean_up_2d(split_line);
		return (NULL);
	}
	texture_path = normal_copy(split_line[1]);
	clean_up_2d(split_line);
	return (texture_path);
}
