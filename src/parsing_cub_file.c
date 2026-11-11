/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:06:16 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/11 12:34:26 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_lines_from_file(const char *file, char **lines, int *exit_code)
{
	int	fd;
	int	i;

	fd = 0;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		*exit_code = 1;
		return ;
	}
	while (1)
	{
		lines[i] = get_next_line(fd, exit_code);
		if (*exit_code)
			break ;
		if (!lines[i])
			break ;
		i++;
	}
    close(fd);
}

char	**parsing_from_file(const char *file)
{
	int		len;
	int		exit_code;
	char	**lines;

	exit_code = 0;
	len = get_len_of_file(file, &exit_code);
    if (len == -1)
    {
        write(2, "Error\nWrong file\n", 17);
        return (NULL);
    }
	lines = ft_calloc(sizeof(char *), len + 1);
	if (!lines)
		return (NULL);
	get_lines_from_file(file, lines, &exit_code);
	if (exit_code)
		return (clean_up_2d(lines), NULL);
	return (lines);
}

char	*create_white_space_set(void)
{
	int		counter;
	int		set_index;
	char	*set;

	counter = BACKSPACE;
	set_index = 0;
	set = ft_calloc(sizeof(char), 8);
	if (!set)
		return (NULL);
	while (counter <= CARRIAGE_RET)
		set[set_index++] = counter++;
	set[set_index++] = SPACE;
	set[set_index] = NULL_TERMINATOR;
	return (set);
}

int	trim_the_read_file(char **read_file)
{
	int		i;
	char	*set;
	int		end_index;

	i = 0;
	end_index = get_2d_len(read_file) - get_first_map_len(read_file);
	set = create_white_space_set();
	if (!set)
		return (clean_up_2d(read_file), 0);
	while (i < end_index)
	{
		read_file[i] = ft_strtrim(read_file[i], set);
		if (!read_file[i])
		{
			clean_up_2d(read_file);
			return (free(set), 0);
		}
		i++;
	}
	free(set);
	return (1);
}

int	get_2d_len(char **split_line)
{
	int	len;

	len = 0;
	while (split_line[len])
		len++;
	return (len);
}

char	*normal_copy(char *original)
{
	int		i;
	char	*new_word;

	i = 0;
	new_word = ft_calloc(sizeof(char), ft_strlen(original) + 1);
	if (!new_word)
		return (NULL);
	while (original[i])
	{
		new_word[i] = original[i];
		i++;
	}
	new_word[i] = NULL_TERMINATOR;
	return (new_word);
}

int	matching_names(char *current_line, char *direction)
{
	if (!ft_strncmp(current_line, direction, 2)
		&& is_white_space(current_line[2]))
		return (1);
	return (0);
}

int	check_missing_textures(t_map *map_struct)
{
	if (!ft_strncmp(map_struct->EA, "", 1))
		return (print_missing_id_error("EA"), 1);
	if (!ft_strncmp(map_struct->WE, "", 1))
		return (print_missing_id_error("WE"), 1);
	if (!ft_strncmp(map_struct->NO, "", 1))
		return (print_missing_id_error("NO"), 1);
	if (!ft_strncmp(map_struct->SO, "", 1))
		return (print_missing_id_error("SO"), 1);
	return (0);
}

int add_colours_to_array(int *colours, char **split_colours)
{
	int	i;

	i = 0;
	while (split_colours[i])
	{
		colours[i] = ft_atoi(split_colours[i]);
        if (colours[i] == -1)
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

int	matching_levels(char *current_line, const char letter)
{
	if (current_line[0] == letter && is_white_space(current_line[1]))
		return (1);
	return (0);
}

int	get_first_map_len(char **read_file)
{
	int	last_index;
	int	len;

	len = 0;
	last_index = get_2d_len(read_file) - 1;
	while (!ft_strncmp("", read_file[last_index], 1))
	{
		last_index--;
		len++;
	}
	return (len);
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

int	get_trimmed_len(char **read_file)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (read_file[i])
	{
		if (ft_strncmp(read_file[i], "", 1))
			len++;
		i++;
	}
	return (len);
}

char	**trim_empty_lines(char **read_file)
{
	char	**trimmed_read_line;
	int		trimmed_len;
	int		i;
	int		trimmed_index;

	i = 0;
	trimmed_index = 0;
	trimmed_len = get_trimmed_len(read_file);
	trimmed_read_line = ft_calloc(sizeof(char *), trimmed_len + 2);
	if (!trimmed_read_line)
		return (NULL);
	while (trimmed_index <= trimmed_len)
	{
		if (ft_strncmp(read_file[i], "", 1))
		{
			trimmed_read_line[trimmed_index] = normal_copy(read_file[i]);
			if (!trimmed_read_line[trimmed_index++])
				return (NULL);
		}
		if (trimmed_index == 6)
        {
			trimmed_read_line[trimmed_index] = ft_strdup("");
            if (!trimmed_read_line[trimmed_index++])
                return (NULL);
        }
		i++;
	}
	clean_up_2d(read_file);
	trimmed_read_line[trimmed_index] = NULL;
	return (trimmed_read_line);
}

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

char	**copy_map(char **old_map)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = ft_calloc(sizeof(char *), get_2d_len(old_map) + 1);
	if (!new_map)
		return (NULL);
	while (old_map[i])
	{
		new_map[i] = normal_copy(old_map[i]);
		if (!new_map[i])
			return (clean_up_2d_until_index(new_map, i), NULL);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

int	flood_fill(char **map, int y, int x)
{
	int	height;

	height = get_2d_len(map);
	if (y < 0 || y > height)
		return (0);
	if (x > ft_strlen(map[y]) || x < 0 || !map[y][x])
		return (0);
	if (is_safe_spot(map[y][x]))
		return (1);
	map[y][x] = 1;
	if (!flood_fill(map, y - 1, x))
		return (0);
	if (!flood_fill(map, y + 1, x))
		return (0);
	if (!flood_fill(map, y, x - 1))
		return (0);
	if (!flood_fill(map, y, x + 1))
		return (0);
	return (1);
}
