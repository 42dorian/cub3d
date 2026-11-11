/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 13:18:01 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/09 13:18:01 by dabdulla         ###   ########.fr       */
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
