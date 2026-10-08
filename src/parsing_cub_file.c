/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:06:16 by bguhty            #+#    #+#             */
/*   Updated: 2026/10/08 23:27:39 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     get_len_of_file(const char *file, int *exit_code)
{
    int fd;
    int len;
    
    len = 0;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (-1);
    while (get_next_line(fd, exit_code))
        len++;
    close(fd);
    return (len);
}

char    **parsing_from_file(const char *file)
{
    int fd;
    int len;
    int i;
    int exit_code;
    char **input;

    i = 0;
    exit_code = 0;
    len = get_len_of_file(file, &exit_code);
    input = ft_calloc(sizeof(char *), len + 1);
    if (!input)
        return (NULL);
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (NULL);
    while (1)
    {
        input[i] = get_next_line(fd, &exit_code);
        if (exit_code)
            return (NULL);
        if (!input[i])
            break ;
        i++;
    }
    return (input);
}

char    *create_white_space_set()
{
    int     counter;
    int     set_index;
    char    *set;
    
    counter = BACKSPACE;
    set_index = 0;
    set = ft_calloc(sizeof(char), 9);
    if (!set)
        return (NULL);
    while (counter <= CARRIAGE_RET)
        set[set_index++] = counter++;
    set[set_index++] = SPACE;
    set[set_index] = NULL_TERMINATOR;
    return (set);
}

int    trim_the_read_file(char **read_file)
{
    int     i;
    char    *set;
    int     end_index;
    
    i = 0;
    end_index = get_len_of_read_file(read_file) - get_first_map_len(read_file);
    set = create_white_space_set();
    if (!set)
        return (0);
    while (i < end_index)
    {
        read_file[i] = ft_strtrim(read_file[i], set);
        if (!read_file[i])
            return (0);
        i++;
    }
    return (1);
}

int     is_end(char letter)
{
    if (is_white_space(letter) || is_null_terminator(letter))
        return (1);
    return (0);
}

int     split_len(char **split_line)
{
    int len;

    len = 0;
    while (split_line[len])
        len++;
    return (len);
}

char    *normal_copy(char *original)
{
    int     i;
    char    *new_word;
    
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

void    split_clean_up(char **split_line)
{
    int i;
    
    i = 0;
    while (split_line[i])
        free(split_line[i++]);
    free(split_line);
}

char    *get_texture(char *line)
{
    char    *texture_path;
    char    **split_line;
    
    split_line = ft_split(line, SPACE);
    if (!split_line)
        return (NULL);
    if (split_len(split_line) != 2)
        return (NULL);
    texture_path = normal_copy(split_line[1]);
    split_clean_up(split_line);
    return (texture_path);
}

char     *get_direction(char **read_file, const char *direction)
{
    int     i;
    
    i = 0;
    while (read_file[i])
    {
        if (read_file[i][0] == direction[0] && read_file[i][1] == direction[1] && is_white_space(read_file[i][2]))
            return (get_texture(read_file[i]));
        i++;
    }
    return (NULL);
}

int     free_texture_paths(t_map *map_struct)
{
    if (ft_strlen(map_struct->EA))
        free(map_struct->EA);
    if (ft_strlen(map_struct->WE))
        free(map_struct->WE);
    if (ft_strlen(map_struct->SO))
        free(map_struct->SO);
    if (ft_strlen(map_struct->NO))
        free(map_struct->NO);
    return (0);
}

int     got_every_texture_path(t_map *map_struct)
{
    if (!ft_strlen(map_struct->EA))
        return (free_texture_paths(map_struct));
    if (!ft_strlen(map_struct->WE))
        return (free_texture_paths(map_struct));
    if (!ft_strlen(map_struct->SO))
        return (free_texture_paths(map_struct));
    if (!ft_strlen(map_struct->NO))
        return (free_texture_paths(map_struct));
    return (1);
}

void     add_colours_to_array(int *colours, char **split_colours)
{
    int i;

    i = 0;
    while (split_colours[i])
    {
        colours[i] = ft_atoi(split_colours[i]);
        i++;
    }
}

int     *get_colour(char *line)
{
    int     *colours;
    char    **split_line;
    char    **split_colours;
    
    colours = ft_calloc(sizeof(int), 4);
    if (!colours)
        return (NULL);
    split_line = ft_split(line, SPACE);
    if (!split_line)
        return (free(colours), NULL);
    if (split_len(split_line) != 2)
        return (split_clean_up(split_line), free(colours), NULL);
    split_colours = ft_split(split_line[1], COMMA);
    if (!split_colours)
        return (split_clean_up(split_line), free(colours), NULL);
    split_clean_up(split_line);
    add_colours_to_array(colours, split_colours);
    split_clean_up(split_colours);
    return (colours);
}

int     *get_levels(char **read_file, const char letter)
{
    int i;

    i = 0;
    while (read_file[i])
    {
        if (read_file[i][0] == letter && is_white_space(read_file[i][1]))
            return (get_colour(read_file[i]));
        i++;
    }
    return (NULL);
}

int     get_first_map_len(char **read_file)
{
    int     last_index;
    int     len;
    
    len = 0;
    last_index = get_len_of_read_file(read_file) - 1;
    while (!is_new_line(read_file[last_index--][0]))
        len++;
    return (len);
}

int     get_second_map_len(char **read_file)
{
    int     last_index;
    int     len;
    
    len = 0;
    last_index = get_len_of_read_file(read_file) - 1;
    while (ft_strncmp(read_file[last_index--], "", 1))
        len++;
    return (len);
}

int     get_map_len(char **map)
{
    int     len;
    
    len = 0;
    while (map[len])
        len++;
    return (len);
}

void    free_map(char **map, int last, int current)
{
    while (last > current)
        free(map[last--]);
    free(map);
}

int     get_len_of_read_file(char **read_file)
{
    int len;

    len = 0;
    while (read_file[len])
        len++;
    return (len);
}

char    **get_map(char **read_file)
{
    char    **map;
    int     last_index;
    int     len;
    
    len = get_second_map_len(read_file);
    last_index = get_len_of_read_file(read_file) - 1;
    map = ft_calloc(sizeof(char *),  len + 1);
    if (!map)
        return (NULL);
    map[len--] = NULL;
    while (ft_strncmp(read_file[last_index], "", 1))
    {
        map[len] = normal_copy(read_file[last_index]);
        if (!map[len])
            return (free_map(map, get_second_map_len(read_file), len), NULL);
        len--;
        last_index--;
    }
    return (map);
}

int     get_struct_values(t_map *map_struct, char **read_file)
{
    map_struct->EA = get_direction(read_file, "EA");
    map_struct->NO = get_direction(read_file, "NO");
    map_struct->WE = get_direction(read_file, "WE");
    map_struct->SO = get_direction(read_file, "SO");
    map_struct->floor = get_levels(read_file, 'F');
    map_struct->ceiling = get_levels(read_file, 'C');
    map_struct->map = get_map(read_file);
    
    if (got_every_texture_path(map_struct))
        return (1);
    return (0);
}

int     is_new_line(char letter)
{
    if (letter == '\n')
        return (1);
    return (0);
}

int     get_trimmed_len(char **read_file)
{
    int len;
    int i;
    
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

char    **trim_empty_lines(char **read_file)
{
    char    **trimmed_read_line;
    int     trimmed_len;
    int     i;
    int     trimmed_index;
    
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
            trimmed_read_line[trimmed_index++] = ft_strdup("");
        i++;
    }
    trimmed_read_line[trimmed_index] = NULL;
    split_clean_up(read_file);
    return (trimmed_read_line);
}

t_map   *creating_t_cub_struct(char **read_file)
{
    t_map   *map_struct;

    map_struct = ft_calloc(sizeof(t_map), 1);
    if (!map_struct)
        return (NULL);
    if (!trim_the_read_file(read_file))
        return (NULL);
    read_file = trim_empty_lines(read_file);
    if (!read_file)
        return (NULL);
    if (!get_struct_values(map_struct, read_file))
        return (NULL);
    return (map_struct);
}

int     is_safe_spot(char letter)
{
    if (letter == '1' || letter == 1)
        return (1);
    return (0);
}

char    **copy_map(char **old_map)
{
    char    **new_map;
    int     i;

    i = 0;
    new_map = ft_calloc(sizeof(char *), get_map_len(old_map));
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

int     flood_fill(char **map, int y, int x)
{
    int height;
    
    height = get_map_len(map);
    if (y < 0 || y > height)
        return (0);
    if (x < 0 || !map[y][x])
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
