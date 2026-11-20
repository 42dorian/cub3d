/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 12:47:39 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/20 19:25:19 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	t_map_clean_up(t_map *game_board)
{
	free(game_board->ceiling);
	game_board->ceiling = NULL;
	free(game_board->ea);
	game_board->ea = NULL;
	free(game_board->floor);
	game_board->floor = NULL;
	free(game_board->no);
	game_board->no = NULL;
	free(game_board->so);
	game_board->so = NULL;
	free(game_board->we);
	game_board->we = NULL;
	clean_up_2d(game_board->map);
	game_board->map = NULL;
	free(game_board);
	game_board = NULL;
}

void	clean_up_2d(char **text)
{
	int	i;

	i = 0;
	if (!text)
		return ;
	while (text[i])
		free(text[i++]);
	free(text);
	text = NULL;
}

void	clean_game(t_cub *game)
{
	int	i;

	i = 0;
	while (i < 4)
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

void	free_map_with_index(char **map, int last, int current)
{
	while (last > current)
		free(map[last--]);
	free(map);
}

char	**copy_map(char **old_map)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = ft_calloc(sizeof(char *), get_2d_len(old_map) + 1);
	if (!new_map)
		return (NULL);
	while (old_map[i])
	{
		new_map[i] = normal_copy(old_map[i]);
		if (!new_map[i])
			return (clean_up_2d_until_index(new_map, i), NULL);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}
