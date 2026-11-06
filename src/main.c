/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:40 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/06 15:35:25 by dabdulla         ###   ########.fr       */
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
	split_clean_up(game_board->map);
	game_board->map = NULL;
	free(game_board);
	game_board = NULL;
}

t_map	*map_parsing(int args, char **argv)
{
	int			exit_code;
	t_map		*game_board;
    char    	**read_file;

	exit_code = 0;
	if (args != 2)
		return (ft_putendl_fd("Error\nNo map spcified!", 2), NULL);
    read_file = parsing_from_file(argv[1]);
	if (!read_file)
		return (NULL);
    game_board = creating_t_cub_struct(read_file);
	if (!game_board)
		return (split_clean_up(read_file), 1);
	split_clean_up(read_file);
    if (!map_is_valid(game_board->map, &exit_code))
        return (t_map_clean_up(game_board), display_invalid_map_message(exit_code), 1);
	else
		args++;
	t_map_clean_up(game_board);
	return (0);
}
