/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 13:02:28 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/09 13:15:20 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	split_clean_up(char **split_line)
{
	int	i;

	i = 0;
	if (!split_line)
		return ;
	while (split_line[i])
		free(split_line[i++]);
	free(split_line);
}

int	free_texture_paths(t_map *map_struct)
{
	free(map_struct->EA);
	free(map_struct->NO);
	free(map_struct->SO);
	free(map_struct->WE);
	free(map_struct->ceiling);
	free(map_struct->floor);
	split_clean_up(map_struct->map);
	free(map_struct);
	return (0);
}

void	t_map_clean_up(t_map *game_board)
{
	free(game_board->ceiling);
	game_board->ceiling = NULL;
	free(game_board->EA);
	game_board->EA = NULL;
	free(game_board->floor);
	game_board->floor = NULL;
	free(game_board->NO);
	game_board->NO = NULL;
	free(game_board->SO);
	game_board->SO = NULL;
	free(game_board->WE);
	game_board->WE = NULL;
	split_clean_up(game_board->map);
	game_board->map = NULL;
	free(game_board);
	game_board = NULL;
}
void clean_game(t_cub *game)
{
	int i;

	i = 0;
	while(i < 4)
	{
		if (game->mlx.mlx_ptr && game->tex[i].img)
			mlx_destroy_image(game->mlx.mlx_ptr, game->tex[i].img);
		i++;
	}
	if (game->mlx.mlx_ptr && game->mlx.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
	if (game->mlx.mlx_ptr && game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	if (game->mlx.mlx_ptr)
	{
		mlx_do_key_autorepeaton(game->mlx.mlx_ptr);
		mlx_destroy_display(game->mlx.mlx_ptr);
	}
	free(game->mlx.mlx_ptr);
	if (game->map)
		t_map_clean_up(game->map);
}
