/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:06:39 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/11 16:41:04 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_cub *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (0);
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, WIDTH, HEIGHT,
			"cub3d");
	if (!game->mlx.win_ptr)
		return (0);
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr, WIDTH, HEIGHT);
	if (!game->mlx.img_ptr)
		return (0);
	game->mlx.addr = mlx_get_data_addr(game->mlx.img_ptr, &game->mlx.bpp,
			&game->mlx.line_len, &game->mlx.endian);
	if (!game->mlx.addr)
		return (0);
	return (1);
}

void	mlx_hooks(t_cub *game)
{
	mlx_loop_hook(game->mlx.mlx_ptr, render_loop, game);
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, key_down, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, key_up, game);
	mlx_hook(game->mlx.win_ptr, 17, 0, mlx_loop_end, game->mlx.mlx_ptr);
	mlx_do_key_autorepeatoff(game->mlx.mlx_ptr);
	mlx_loop(game->mlx.mlx_ptr);
}
