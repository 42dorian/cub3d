/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_directions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 13:18:39 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/10 13:18:51 by bguhty           ###   ########.fr       */
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
