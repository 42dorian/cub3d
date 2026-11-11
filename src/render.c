/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   #include "cub3d.h".c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 12:42:14 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/11 16:40:54 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_column(t_cub *game, int x);

void	put_pixel(t_mlx *mlx, int row, int col, int color)
{
	char	*dst;

	if (col < 0 || col >= WIDTH || row < 0 || row >= HEIGHT)
		return ;
	dst = mlx->addr + (row * mlx->line_len + col * (mlx->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static int	get_color(int *rgb)
{
	int	color;

	color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	return (color);
}

static void	draw_column(t_cub *game, int x)
{
	t_tex	*t;
	int		line_h;
	int		top;
	int		tex_x;
	int		y;

	line_h = (int)(HEIGHT / game->ray.perp_dist);
	top = HEIGHT / 2 - line_h / 2;
	y = 0;
	while (y < top && y < HEIGHT)
		put_pixel(&game->mlx, y++, x, get_color(game->map->ceiling));
	t = tex_selector(game);
	tex_x = get_tex_x(game, t);
	while (y < top + line_h && y < HEIGHT)
	{
		put_pixel(&game->mlx, y, x, get_texture_color(t, tex_x, (y - top)
				* t->height / line_h));
		y++;
	}
	while (y < HEIGHT)
		put_pixel(&game->mlx, y++, x, get_color(game->map->floor));
}

int	render_loop(t_cub *game)
{
	key_hook(game);
	render_frame(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.img_ptr, 0, 0);
	return (0);
}

void	render_frame(t_cub *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_rays(game, x);
		init_step_and_side(game);
		dda_loop(game);
		if (game->ray.side == 0)
			game->ray.perp_dist = game->ray.side_x - game->ray.delta_x;
		else
			game->ray.perp_dist = game->ray.side_y - game->ray.delta_y;
		draw_column(game, x);
		x++;
	}
}
