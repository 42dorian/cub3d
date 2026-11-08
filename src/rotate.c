/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 14:52:40 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/08 15:17:56 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_cub *game, int keycode)
{
	double	angle;
	double	old_cam_x;
	double	old_dir_x;

	if (keycode == LEFT_KEY)
		angle = -1 * ROTATE_SPEED;
	else if (keycode == RIGHT_KEY)
		angle = 1 * ROTATE_SPEED;
	else
		return ;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = old_dir_x * cos(angle) - game->player.dir_y
		* sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y
		* cos(angle);
	old_cam_x = game->player.cam_x;
	game->player.cam_x = old_cam_x * cos(angle) - game->player.cam_y
		* sin(angle);
	game->player.cam_y = old_cam_x * sin(angle) + game->player.cam_y
		* cos(angle);
}
