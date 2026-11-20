/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:40 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/20 19:43:37 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(t_map *map, t_player *player)
{
	int	row;
	int	column;

	row = 0;
	column = 0;
	while (map->map[row])
	{
		column = 0;
		while (map->map[row][column])
		{
			if (is_player(map->map[row][column]))
			{
				init_player(player, row, column, map->map[row][column]);
				return ;
			}
			column++;
		}
		row++;
	}
}

int	valid_file_type(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (len <= 4 || file_name[len - 5] == '/' || ft_strncmp(file_name + len - 4,
			".cub", 4))
		return (0);
	return (1);
}

t_map	*map_parsing(int args, char **argv)
{
	int		exit_code;
	t_map	*game_board;
	char	**read_file;

	exit_code = 0;
	if (args == 1)
		return (ft_putendl_fd("Error\nNo map spcified!", 2), NULL);
	if (args > 2)
		return (ft_putendl_fd("Error\nMultiple maps specified!", 2), NULL);
	if (!valid_file_type(argv[1]))
		return (ft_putendl_fd("Error\nInvalid file type!", 2), NULL);
	read_file = parsing_from_file(argv[1]);
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
	if (!init_mlx(&game))
		return (clean_game(&game), 1);
	mlx_hooks(&game);
	clean_game(&game);
	return (0);
}
