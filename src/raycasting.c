/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 15:22:18 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/11 16:41:19 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rays(t_cub *game, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / WIDTH - 1;
	game->ray.ray_x = game->player.dir_x + game->player.cam_x * camera_x;
	game->ray.ray_y = game->player.dir_y + game->player.cam_y * camera_x;
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
	if (game->ray.ray_x == 0)
		game->ray.delta_x = 1e30;
	else
		game->ray.delta_x = 1 / fabs(game->ray.ray_x);
	if (game->ray.ray_y == 0)
		game->ray.delta_y = 1e30;
	else
		game->ray.delta_y = 1 / fabs(game->ray.ray_y);
}

void	init_step_and_side(t_cub *game)
{
	if (game->ray.ray_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_x = (game->player.pos_x - game->ray.map_x)
			* game->ray.delta_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_x = (game->ray.map_x + 1 - game->player.pos_x)
			* game->ray.delta_x;
	}
	if (game->ray.ray_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_y = (game->player.pos_y - game->ray.map_y)
			* game->ray.delta_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_y = (game->ray.map_y + 1 - game->player.pos_y)
			* game->ray.delta_y;
	}
}

void	dda_loop(t_cub *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->ray.side_x < game->ray.side_y)
		{
			game->ray.side_x += game->ray.delta_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_y += game->ray.delta_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (game->map->map[game->ray.map_y][game->ray.map_x] == '1')
			hit = 1;
	}
}
