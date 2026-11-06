/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:40 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/05 12:53:00 by dabdulla         ###   ########.fr       */
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
		return (NULL);
    if (!map_is_valid(game_board->map, &exit_code))
        return (display_invalid_map_message(exit_code), t_map_clean_up(game_board), NULL);
    return (game_board);
}

int is_player(char p)
{
	if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
		return (1);
	return (0);
}

void set_north(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->cam_x = 0.66;
	player->cam_y = 0;
}

void set_south(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 1;
	player->cam_x = -0.66;
	player->cam_y = 0;
}

void set_east(t_player *player)
{
	player->dir_x = 1;
	player->dir_y = 0;
	player->cam_x = 0;
	player->cam_y = 0.66;
}

void set_west(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->cam_x = 0;
	player->cam_y = -0.66;
}

void init_player(t_player *player, int row, int column, char pos)
{
	player->pos_y = row + 0.5;
	player->pos_x = column + 0.5;
	if (pos == 'N')
		set_north(player);
	if (pos == 'S')
		set_south(player);
	if (pos == 'E')
		set_east(player);
	if (pos == 'W')
		set_west(player);
}

void print_player_position(t_map *map, t_player *player)
{
	int row = 0;
	int column = 0;

	while (map->map[row])
	{
		column = 0;
		while(map->map[row][column])
		{
			if (is_player(map->map[row][column]))
			{
				printf("Row: %i, Column: %i\n", row, column);
				init_player(player, row, column, map->map[row][column]);
				printf("Player Pos: (%f, %f), Player Dir: (%f, %f), Player Plane: (%f, %f)\n", player->pos_y, player->pos_x, player->dir_y, player->dir_x, player->cam_y, player->cam_x);
				return ;
			}
			column++;
		}
		row++;
	}
	printf("No player found!\n");
}


int	main(int args, char **argv)
{
	t_cub game;

	ft_bzero(&game, sizeof(game));
	game.map = map_parsing(args, argv);
	if (!game.map)
		return (1);
	print_player_position(game.map, &game.player);
	game.mlx.mlx_ptr = mlx_init();
	if (!game.mlx.mlx_ptr)
		return (1);
	game.mlx.win_ptr = mlx_new_window(game.mlx.mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!game.mlx.win_ptr)
		return (1);
	game.mlx.img_ptr = mlx_new_image(game.mlx.mlx_ptr, WIDTH, HEIGHT);
	if (!game.mlx.img_ptr)
		return (1);
	game.mlx.addr = mlx_get_data_addr(game.mlx.img_ptr, &game.mlx.bpp, &game.mlx.line_len, &game.mlx.endian);
	if (!game.mlx.addr)
		return (1);
	// put_color(&game.mlx);
	render_frame(&game);
	mlx_put_image_to_window(game.mlx.mlx_ptr, game.mlx.win_ptr, game.mlx.img_ptr, 0, 0);
	mlx_loop(game.mlx.mlx_ptr);
	t_map_clean_up(game.map);
	return (0);
}
