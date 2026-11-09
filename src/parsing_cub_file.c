/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:06:16 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/09 13:12:13 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_len_of_file(const char *file, int *exit_code)
{
	char	*curr;
	int		fd;
	int		len;

	len = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (1)
	{
		curr = get_next_line(fd, exit_code);
		if (!curr)
			break ;
		len++;
		free(curr);
	}
	close(fd);
	if (*exit_code)
		return (-1);
	return (len);
}

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
		return (split_clean_up(lines), NULL);
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
	end_index = get_len_of_read_file(read_file) - get_first_map_len(read_file);
	set = create_white_space_set();
	if (!set)
		return (0);
	while (i < end_index)
	{
		read_file[i] = ft_strtrim(read_file[i], set);
		if (!read_file[i])
		{
			free_strs(read_file, i);
			free(set);
			return (0);
		}
		i++;
	}
	free(set);
	return (1);
}

int	is_end(char letter)
{
	if (is_white_space(letter) || is_null_terminator(letter))
		return (1);
	return (0);
}

int	split_len(char **split_line)
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

char	*get_texture(char *line)
{
	char	*texture_path;
	char	**split_line;

	split_line = ft_split(line, SPACE);
	if (!split_line)
		return (NULL);
	if (split_len(split_line) == 1)
	{
		print_missing_texture_pack(split_line[0]);
		split_clean_up(split_line);
		return (NULL);
	}
	else if (split_len(split_line) > 2)
	{
		print_multiple_texture_packs(split_line[0]);
		split_clean_up(split_line);
		return (NULL);
	}
	texture_path = normal_copy(split_line[1]);
	split_clean_up(split_line);
	return (texture_path);
}

int	matching_names(char *current_line, char *direction)
{
	if (!ft_strncmp(current_line, direction, 2)
		&& is_white_space(current_line[2]))
		return (1);
	return (0);
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



void	print_texture_error_message(const char *abbrev)
{
	write(2, "Error\nMissing ", 14);
	write(2, abbrev, ft_strlen(abbrev));
	write(2, " identifier\n", 12);
}

int	check_missing_textures(t_map *map_struct)
{
	if (!ft_strncmp(map_struct->EA, "", 1))
		return (print_texture_error_message("EA"), 1);
	if (!ft_strncmp(map_struct->WE, "", 1))
		return (print_texture_error_message("WE"), 1);
	if (!ft_strncmp(map_struct->NO, "", 1))
		return (print_texture_error_message("NO"), 1);
	if (!ft_strncmp(map_struct->SO, "", 1))
		return (print_texture_error_message("SO"), 1);
	if (!map_struct->floor)
		return (print_texture_error_message("F"), 1);
	if (!map_struct->ceiling)
		return (print_texture_error_message("C"), 1);
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
            write(2, "Error\nAll colours' codes must be", 32);
            write(2, " in the following range: 0-255\n", 31);
            free(colours);
            colours = NULL;
            return (0);
        }
		i++;
	}
    return (1);
}

void	print_missing_texture_pack(char *level)
{
	write(2, "Error\n", 6);
	write(2, level, ft_strlen(level));
	write(2, " identifier\n", 12);
}

void	print_multiple_texture_packs(char *level)
{
	write(2, "Error\nMultiple texture packs for ", 33);
	write(2, level, ft_strlen(level));
	write(2, "\n", 1);
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
	if (split_len(*split_line) == 1)
	{
		print_missing_texture_pack(*split_line[0]);
		split_clean_up(*split_line);
		free(*colours);
		return (0);
	}
	else if (split_len(*split_line) > 2)
	{
		print_multiple_texture_packs(*split_line[0]);
		split_clean_up(*split_line);
		free(*colours);
		return (0);
	}
	return (1);
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
		return (split_clean_up(split_line), free(colours), NULL);
	split_clean_up(split_line);
	if (!add_colours_to_array(colours, split_colours))
        return (split_clean_up(split_colours), NULL);
	split_clean_up(split_colours);
	return (colours);
}

int	matching_levels(char *current_line, const char letter)
{
	if (current_line[0] == letter && is_white_space(current_line[1]))
		return (1);
	return (0);
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
	return (NULL);
}

int	get_first_map_len(char **read_file)
{
	int	last_index;
	int	len;

	len = 0;
	last_index = get_len_of_read_file(read_file) - 1;
	while (!is_new_line(read_file[last_index][0]) && last_index != 0)
	{
		last_index--;
		len++;
	}
	return (len);
}

int	get_map_len_from_file(char **read_file)
{
	int	last_index;
	int	len;

	len = 0;
	last_index = get_last_index(read_file);
	while (ft_strncmp(read_file[last_index--], "", 1))
		len++;
	return (len);
}

int	get_map_len(char **map)
{
	int	len;

	len = 0;
	while (map[len])
		len++;
	return (len);
}

void	free_map(char **map, int last, int current)
{
	while (last > current)
		free(map[last--]);
	free(map);
}

int	get_len_of_read_file(char **read_file)
{
	int	len;

	len = 0;
	while (read_file[len])
		len++;
	return (len);
}

char	**get_map(char **read_file)
{
	char	**map;
	int		last_index;
	int		len;

	len = get_map_len_from_file(read_file);
	last_index = get_len_of_read_file(read_file) - 1;
	map = ft_calloc(sizeof(char *), len + 1);
	if (!map)
		return (NULL);
	map[len--] = NULL;
	while (len >= 0)
	{
		map[len] = normal_copy(read_file[last_index]);
		if (!map[len])
			return (free_map(map, get_map_len_from_file(read_file), len), NULL);
		len--;
		last_index--;
	}
	return (map);
}

int	get_struct_values(t_map *map_struct, char **read_file)
{
	map_struct->EA = get_direction(read_file, "EA");
	if (!map_struct->EA)
		return (0);
	map_struct->NO = get_direction(read_file, "NO");
	if (!map_struct->NO)
		return (free_texture_paths(map_struct));
	map_struct->WE = get_direction(read_file, "WE");
	if (!map_struct->WE)
		return (free_texture_paths(map_struct));
	map_struct->SO = get_direction(read_file, "SO");
	if (!map_struct->SO)
		return (free_texture_paths(map_struct));
	map_struct->floor = get_levels(read_file, 'F');
	if (!map_struct->floor)
		return (free_texture_paths(map_struct));
	map_struct->ceiling = get_levels(read_file, 'C');
	if (!map_struct->ceiling)
		return (free_texture_paths(map_struct));
	map_struct->map = get_map(read_file);
	if (!map_struct->map)
		return (free_texture_paths(map_struct));
	if (check_missing_textures(map_struct))
		return (free_texture_paths(map_struct));
	return (1);
}

int	is_new_line(char letter)
{
	if (letter == '\n')
		return (1);
	return (0);
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
	trimmed_read_line[trimmed_index] = NULL;
	return (trimmed_read_line);
}

int	get_last_index(char **read_file)
{
	int	last_index;

	last_index = get_len_of_read_file(read_file) - 1;
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

int	get_first_index(char **read_file)
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
	free(texture_set);
	return (biggest_index);
}

int	is_valid_input(char **read_file)
{
	int	first_index;
	int	last_index;

	last_index = get_last_index(read_file);
	first_index = get_first_index(read_file) + 1;
	if (first_index == -1)
		return (0);
	while (!ft_strlen(read_file[first_index]))
		first_index++;
	while (first_index < last_index)
	{
		if (!ft_strlen(read_file[first_index]))
			return (0);
		first_index++;
	}
	return (1);
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
		return (t_map_clean_up(map_struct), write(2, "Error\nInvalid input\n",
				20), NULL);
	read_file = trim_empty_lines(read_file);
	if (!read_file)
		return (t_map_clean_up(map_struct), NULL);
	if (!get_struct_values(map_struct, read_file))
		return (split_clean_up(read_file), NULL);
	split_clean_up(read_file);
	return (map_struct);
}

int	is_safe_spot(char letter)
{
	if (letter == '1' || letter == 1)
		return (1);
	return (0);
}

char	**copy_map(char **old_map)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = ft_calloc(sizeof(char *), get_map_len(old_map) + 1);
	if (!new_map)
		return (NULL);
	while (old_map[i])
	{
		new_map[i] = normal_copy(old_map[i]);
		if (!new_map[i])
			return (free_strs(new_map, i), NULL);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

int	flood_fill(char **map, int y, int x)
{
	int	height;

	height = get_map_len(map);
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
