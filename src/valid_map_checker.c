/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 10:23:12 by bguhty            #+#    #+#             */
/*   Updated: 2026/10/08 23:37:07 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_null_terminator(char letter)
{
    if (letter == NULL_TERMINATOR)
        return (1);
    return (0);
}

int empty_on_the_right(char *line, int column)
{
    if (is_white_space(line[column + 1]) || is_null_terminator(line[column + 1]))
        return (1);
    return (0);
}

int empty_on_the_left(char *line, int column)
{
    if (column > 0 && is_white_space(line[column - 1]))
        return (1);
    return (0);
}

int empty_on_the_top(char **map, int row, int column)
{
    if (row > 0 && is_white_space(map[row - 1][column]))
        return (1);
    return (0);
}

int empty_on_the_bottom(char **map, int row, int column)
{
    int last_row_index;

    last_row_index = map_len(map) - 1;
    if (row != last_row_index && is_white_space(map[row + 1][column]))
        return (1);
    return (0);
}

int sorrund_checker(char **map, int row, int column)
{
    if (is_white_space(map[row][column]))
        return (0);
    if (!empty_on_the_bottom(map, row, column))
        return (0);
    else if (!empty_on_the_top(map, row, column))
        return (0);
    else if (!empty_on_the_left(map[row], column))
        return (0);
    else if (!empty_on_the_right(map[row], column))
        return (0);
    return (1);
}

int any_standing_alone(char **map, int *exit_code)
{
    int row;
    int column;

    row = 0;
    column = 0;
    while (map[row])
    {
        while (map[row][column])
        {
            if (sorrund_checker(map, row, column))
                return (*exit_code = 3, 1);
            column++;
        }
        column = 0;
        row++;
    }
    return (0);
}

int map_len(char **map)
{
    int len;
    
    len = 0;
    if (!map)
        return (len);
    while (map[len])
        len++;
    return (len);
}

int is_white_space(char letter)
{
    if ((letter <= CARRIAGE_RET && letter >= BACKSPACE) || letter == SPACE)
        return (1);
    return (0);
}

int first_wall_index(char *curr_line)
{
    int i;

    i = 0;
    while (is_white_space(curr_line[i]))
        i++;
    return (i);
}

int last_wall_index(char *curr_line)
{
    int i;
    
    i = ft_strlen(curr_line) - 1;
    while (is_white_space(curr_line[i]))
        i--;
    return (i);
}

int is_line_valid(char *line)
{
    int start;
    int end;
    
    start = first_wall_index(line);
    end = last_wall_index(line);
    while (start < end)
    {
        if (line[start] != '1')
            return (0);
        start++;
    }
    return (1);
}

int first_and_last_line(char **map)
{
    int last;

    last = map_len(map) - 1;
    if (last == -1)
        return (0);
    if (!is_line_valid(map[0]))
        return (0);
    if (!is_line_valid(map[last]))
        return (0);
    return (1);
}

int is_wall(char letter)
{
    if (letter == '1')
        return (1);
    return (0);
}

int left_side_covered(char **map)
{
    int index;
    int end;
    int row;
    
    row = 0;
    index = first_wall_index(map[0]);
    end = map_len(map) - 1;
    while (row < end)
    {
        if (!is_wall(map[row + 1][index]))
        {
            while (is_wall(map[row][index]) && map[row + 1][index] != '1')
                index++;
            if (!is_wall(map[row][index]))
                return (0);
        }
        row++;
    }
    return (1);
}

int right_side_covered(char **map)
{
    int index;
    int row;
    
    row = map_len(map) - 1;
    index = last_wall_index(map[row]);
    while (row > 0)
    {
        if (!is_wall(map[row - 1][index]))
        {
            while (is_wall(map[row][index]) && !is_wall(map[row - 1][index]))
                index--;
            if (!is_wall(map[row][index]))
                return (0);
        }
        row--;
    }
    return (1);
}

int sorrunded_by_walls(char **map, int *exit_code)
{
    if (!first_and_last_line(map))
        return (*exit_code = 4, 0);
    if (!right_side_covered(map))
        return (*exit_code = 4, 0);
    if (!left_side_covered(map))
        return (*exit_code = 4, 0);
    return (1);
}

int is_character(char letter)
{
    if (letter == W || letter == S || letter == N || letter == E)
        return (1);
    return (0);
}

int get_x_of_start(char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[i])
    {
        while (map[i][j])
        {
            if (is_character(map[i][j]))
                return (j);
            j++;
        }
        j = 0;
        i++;
    }
    return (-1);
}

int get_y_of_start(char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[i])
    {
        while (map[i][j])
        {
            if (is_character(map[i][j]))
                return (i);
            j++;
        }
        j = 0;
        i++;
    }
    return (-1);
}

int map_is_valid(char **map, int *exit_code)
{
    char    **fake_map;
    int     x;
    int     y;
    
    x = get_x_of_start(map);
    y = get_y_of_start(map);
    if (!characters_check(map, exit_code))
        return (0);
    if (any_standing_alone(map, exit_code))
        return (0);
    convert_spaces_to_zeroes(map);
    fake_map = copy_map(map);
    if (!fake_map)
        return (0);
    if (!flood_fill(fake_map, y, x))
        return (*exit_code = 4, 0);
    return (1);
}

void    convert_spaces_to_zeroes(char **map)
{
    int start;
    int end;
    int i;

    i = 1;
    while (map[i])
    {
        start = first_wall_index(map[i]);
        end = last_wall_index(map[i]);
        while (start < end)
        {
            if (is_white_space(map[i][start]))
                map[i][start] = '0';
            start++;
        }
        i++;
    }
}

int valid_char(char letter, int *news, int *exit_code)
{
    if (letter == N || letter == S || letter == W || letter == E)
    {
        if (*news)
        {
            *exit_code = 1;
            return (0);
        }
        else
            *news = letter;
    }
    else if (letter != ONE && letter != ZERO && !is_white_space(letter))
    {
        *exit_code = 2;
        return (0);
    }
    return (1);
}

int characters_check(char **map, int *exit_code)
{
    int news;
    int i;
    int j;
    
    news = 0;
    i = 0;
    j = 0;
    while (map[i])
    {
        while (map[i][j])
        {
            if (!valid_char(map[i][j], &news, exit_code))
                return (0);
            j++;
        }
        j = 0;
        i++;
    }
    return (1);
}

void    display_invalid_map_message(int exit_code)
{
    if (exit_code == 1)
        write(2, "Multiple starting positions!\n", 29);
    else if (exit_code == 2)
        write(2, "Invalid character on the board!\n", 32);
    else if (exit_code == 3)
        write (2, "Additional island(s)!\n", 22);
    else if (exit_code == 4)
        write (2, "The island is not completely surrounded by walls!\n", 50);
}

int main()
{
    int exit_code;
    t_map *map;
    char    **read_file;
    const char    *file;
    file = "cub_test.txt";
    read_file = parsing_from_file(file);
    map = creating_t_cub_struct(read_file);
    exit_code = 0;
    if (!map_is_valid(map->map, &exit_code))
        return (display_invalid_map_message(exit_code), 1);
    return (0);
}
