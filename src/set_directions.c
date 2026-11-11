/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_directions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 13:18:39 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/11 16:12:05 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_north(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->cam_x = 0.66;
	player->cam_y = 0;
}

void	set_south(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 1;
	player->cam_x = -0.66;
	player->cam_y = 0;
}

void	set_east(t_player *player)
{
	player->dir_x = 1;
	player->dir_y = 0;
	player->cam_x = 0;
	player->cam_y = 0.66;
}

void	set_west(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->cam_x = 0;
	player->cam_y = -0.66;
}

void	init_player(t_player *player, int row, int column, char pos)
{
	player->pos_y = row + 0.5;
	player->pos_x = column + 0.5;
	if (pos == 'N')
		set_north(player);
	if (pos == 'S')
		set_south(player);
	if (pos == 'E')
		set_east(player);
	if (pos == 'W')
		set_west(player);
}

void	find_player(t_map *map, t_player *player)
{
	int	row;
	int	column;

	row = 0;
	column = 0;
	while (map->map[row])
	{
		column = 0;
		while (map->map[row][column])
		{
			if (is_player(map->map[row][column]))
			{
				init_player(player, row, column, map->map[row][column]);
				return ;
			}
			column++;
		}
		row++;
	}
}
