/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 12:47:39 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/10 23:40:47 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	free_map_with_index(char **map, int last, int current)
{
	while (last > current)
		free(map[last--]);
	free(map);
}
