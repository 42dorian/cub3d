/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:40 by dabdulla          #+#    #+#             */
/*   Updated: 2026/10/12 23:57:03 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	t_map_clean_up(t_map *game_board)
{
	free(game_board->ceiling);
	free(game_board->EA);
	free(game_board->floor);
	free(game_board->NO);
	free(game_board->SO);
	free(game_board->WE);
	split_clean_up(game_board->map);
	free(game_board);
}

int	main()//int args, char **argv)
{
	int			args = 2;
	const char	*file_name = "cub_test.txt";
	int			exit_code;
    t_map		*game_board;
    char    	**read_file;
	
	exit_code = 0;
	if (args != 2)
		return (1);
    read_file = parsing_from_file(file_name);
	if (!read_file)
		return (1);
    game_board = creating_t_cub_struct(read_file);
	if (!game_board)
		return (1);
    if (!map_is_valid(game_board->map, &exit_code))
        return (display_invalid_map_message(exit_code), 1);
	else
		t_map_clean_up(game_board);
	return (0);
}
