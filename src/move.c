/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 14:14:07 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/08 14:51:42 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int wall_check(t_cub *game, double y, double x)
{
	if (game->map->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

static double wall_offset(double step)
{
	if (step > 0)
		return (WALL_OFFSET);
	return (-WALL_OFFSET);
}

void move_sideways(t_cub *game, int keycode)
{
	int sign;
	double new_x;
	double new_y;
	double step_x;
	double step_y;

	if (keycode == D_KEY)
		sign = 1;
	else if (keycode == A_KEY)
		sign = -1;
	else
		return ;
	step_x = sign * game->player.cam_x * MOVE_SPEED;
	new_x = game->player.pos_x + step_x;
	if (!wall_check(game, game->player.pos_y, new_x + wall_offset(step_x)))
		game->player.pos_x = new_x;
	step_y = sign * game->player.cam_y * MOVE_SPEED;
	new_y = game->player.pos_y + step_y;
	if (!wall_check(game, new_y + wall_offset(step_y), game->player.pos_x))
		game->player.pos_y = new_y;
}

void move_forward(t_cub *game, int keycode)
{
	int sign;
	double new_y;
	double new_x;
	double step_x;
	double step_y;

	if (keycode == W_KEY)
		sign = 1;
	else if (keycode == S_KEY)
		sign = -1;
	else
		return ;
	step_y = sign * game->player.dir_y * MOVE_SPEED;
	new_y = game->player.pos_y + step_y;
	if (!wall_check(game, new_y + wall_offset(step_y), game->player.pos_x))
		game->player.pos_y = new_y;
	step_x = sign * game->player.dir_x * MOVE_SPEED;
	new_x = game->player.pos_x + step_x;
	if (!wall_check(game, game->player.pos_y, new_x + wall_offset(step_x)))
		game->player.pos_x = new_x;
}
