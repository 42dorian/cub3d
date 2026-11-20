/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 20:29:23 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/11 15:59:07 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_image(t_cub *game, t_tex *t, char *p)
{
	t->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, p, &t->width, &t->height);
	if (!t->img)
		return (0);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
	return (1);
}

int	load_images(t_cub *g)
{
	if (!load_image(g, &g->tex[0], g->map->no))
		return (0);
	if (!load_image(g, &g->tex[1], g->map->so))
		return (0);
	if (!load_image(g, &g->tex[2], g->map->we))
		return (0);
	if (!load_image(g, &g->tex[3], g->map->ea))
		return (0);
	return (1);
}

t_tex	*tex_selector(t_cub *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.step_x > 0)
			return (&game->tex[2]);
		return (&game->tex[3]);
	}
	if (game->ray.step_y > 0)
		return (&game->tex[0]);
	return (&game->tex[1]);
}

int	get_tex_x(t_cub *game, t_tex *t)
{
	double	wall_x;
	int		tex_x;

	if (game->ray.side == 0)
		wall_x = game->player.pos_y + game->ray.perp_dist * game->ray.ray_y;
	else
		wall_x = game->player.pos_x + game->ray.perp_dist * game->ray.ray_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * t->width);
	if ((game->ray.side == 0 && game->ray.ray_x > 0) || (game->ray.side == 1
			&& game->ray.ray_y < 0))
		tex_x = t->width - tex_x - 1;
	return (tex_x);
}

int	get_texture_color(t_tex *t, int tex_x, int tex_y)
{
	char	*pixel;

	pixel = t->addr + tex_y * t->line_len + tex_x * (t->bpp / 8);
	return (*(unsigned int *)pixel);
}
