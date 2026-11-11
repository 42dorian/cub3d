/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 15:22:18 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/11 15:22:51 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_mlx *mlx, int row, int col, int color)
{
	char	*dst;

	if (col < 0 || col >= WIDTH || row < 0 || row >= HEIGHT)
		return ;
	dst = mlx->addr + (row * mlx->line_len + col * (mlx->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	put_color(t_mlx *mlx)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (row < HEIGHT)
	{
		col = 0;
		while (col < WIDTH)
		{
			put_pixel(mlx, row, col, 0xFF0000);
			col++;
		}
		row++;
	}
}

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
