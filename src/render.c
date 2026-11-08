/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   #include "cub3d.h".c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:42:14 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/08 15:33:54 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void draw_column(t_cub *game, int x);

void put_pixel(t_mlx *mlx, int row, int col, int color)
{
	char *dst;

	if (col < 0 || col >= WIDTH || row < 0 || row >= HEIGHT)
		return ;
	dst = mlx->addr + (row * mlx->line_len + col * (mlx->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void put_color(t_mlx *mlx)
{
	int row = 0;
	int col = 0;

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

static void dda_loop(t_cub *game)
{
	int hit;

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

static int get_color(int *rgb)
{
	int color;

	color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (color);
}

static void draw_column(t_cub *game, int x)
{
	int line_h;
	int start;
	int end;
	int y;

	line_h = (int)(HEIGHT / game->ray.perp_dist);
	y = 0;
	start = HEIGHT / 2 - line_h / 2;
	end = HEIGHT / 2 + line_h / 2;
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	while (y < start)
		put_pixel(&game->mlx, y++, x, get_color(game->map->ceiling));
	while (y <= end)
		put_pixel(&game->mlx, y++, x, 0x008080);
	while (y < HEIGHT)
		put_pixel(&game->mlx, y++, x, get_color(game->map->floor));
}

void render_frame(t_cub *game)
{
	t_player *p;
	double camera_x;
	int x;

	p = &game->player;
	x = 0;
	while (x < WIDTH)
	{
		camera_x = 2.0 * x / WIDTH - 1;
		game->ray.ray_x = p->dir_x + p->cam_x * camera_x;
		game->ray.ray_y = p->dir_y + p->cam_y * camera_x;
		game->ray.map_x = (int)p->pos_x;
		game->ray.map_y = (int)p->pos_y;
		if (game->ray.ray_x == 0)
			game->ray.delta_x = 1e30;
		else
			game->ray.delta_x = 1 / fabs(game->ray.ray_x);
		if (game->ray.ray_y == 0)
			game->ray.delta_y = 1e30;
		else
			game->ray.delta_y = 1 / fabs(game->ray.ray_y);
		if (game->ray.ray_x < 0)
			game->ray.step_x = -1;
		else
			game->ray.step_x = 1;
		if (game->ray.ray_y < 0)
			game->ray.step_y = -1;
		else
			game->ray.step_y = 1;
		if (game->ray.step_x == -1)
			game->ray.side_x = (p->pos_x - game->ray.map_x) * game->ray.delta_x;
		else
			game->ray.side_x = (game->ray.map_x + 1 - p->pos_x) * game->ray.delta_x;
		if (game->ray.step_y == -1)
			game->ray.side_y = (p->pos_y - game->ray.map_y) * game->ray.delta_y;
		else
			game->ray.side_y = (game->ray.map_y + 1 - p->pos_y) * game->ray.delta_y;
		dda_loop(game);
		if (game->ray.side == 0)
			game->ray.perp_dist = game->ray.side_x - game->ray.delta_x;
		else
			game->ray.perp_dist = game->ray.side_y - game->ray.delta_y;
		draw_column(game, x);
		x++;
	}
}
