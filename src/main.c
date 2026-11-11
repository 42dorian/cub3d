/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:40 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/11 16:41:11 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*map_parsing(int args, char **argv)
{
	int			exit_code;
	t_map		*game_board;
	char		**read_file;
	const char	*file_name;

	file_name = "cub_test.txt";
	(void)argv;
	exit_code = 0;
	if (args == 1)
		return (ft_putendl_fd("Error\nNo map spcified!", 2), NULL);
	if (args > 2)
		return (ft_putendl_fd("Error\nMultiple maps specified!", 2), NULL);
	read_file = parsing_from_file(file_name);
	if (!read_file)
		return (NULL);
	game_board = creating_t_cub_struct(read_file);
	if (!game_board)
		return (NULL);
	if (!map_is_valid(game_board->map, &exit_code))
		return (t_map_clean_up(game_board), NULL);
	return (game_board);
}

int	main(int args, char **argv)
{
	t_cub	game;

	ft_bzero(&game, sizeof(game));
	game.map = map_parsing(args, argv);
	if (!game.map)
		return (1);
	find_player(game.map, &game.player);
	if (!init_mlx(&game) || !load_images(&game))
		return (clean_game(&game), 1);
	mlx_hooks(&game);
	clean_game(&game);
	return (0);
}
