/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 14:59:50 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/08 15:13:46 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_down(int keycode, t_cub *game)
{
	if (keycode == A_KEY)
		game->keys.a_key = 1;
	if (keycode == D_KEY)
		game->keys.d_key = 1;
	if (keycode == W_KEY)
		game->keys.w_key = 1;
	if (keycode == S_KEY)
		game->keys.s_key = 1;
	if (keycode == LEFT_KEY)
		game->keys.left_key = 1;
	if (keycode == RIGHT_KEY)
		game->keys.right_key = 1;
	return (0);
}

int	key_up(int keycode, t_cub *game)
{
	if (keycode == A_KEY)
		game->keys.a_key = 0;
	if (keycode == D_KEY)
		game->keys.d_key = 0;
	if (keycode == W_KEY)
		game->keys.w_key = 0;
	if (keycode == S_KEY)
		game->keys.s_key = 0;
	if (keycode == LEFT_KEY)
		game->keys.left_key = 0;
	if (keycode == RIGHT_KEY)
		game->keys.right_key = 0;
	if (keycode == ESC_KEY)
		mlx_loop_end(game->mlx.mlx_ptr);
	return (0);
}
