/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 10:23:12 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/11 12:32:30 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	first_wall_index(char *curr_line)
{
	int	i;

	i = 0;
	while (is_white_space(curr_line[i]))
		i++;
	return (i);
}

int	last_wall_index(char *curr_line)
{
	int	i;

	i = ft_strlen(curr_line) - 1;
	while (is_white_space(curr_line[i]))
		i--;
	return (i);
}

int	is_line_valid(char *line)
{
	int	start;
	int	end;

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

int	map_is_valid(char **map, int *exit_code)
{
	char	**fake_map;
	int		x;
	int		y;

	x = get_x_of_start(map);
	y = get_y_of_start(map);
	if (!player_check(map, exit_code))
		return (print_invalid_map_message(*exit_code), 0);
	convert_spaces_to_zeroes(map);
	fake_map = copy_map(map);
	if (!fake_map)
		return (0);
	if (!flood_fill(fake_map, y, x))
	{
		*exit_code = 4;
		clean_up_2d(fake_map);
		print_invalid_map_message(*exit_code);
		return (0);
	}
	clean_up_2d(fake_map);
	return (1);
}

void	convert_spaces_to_zeroes(char **map)
{
	int	start;
	int	end;
	int	i;

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
