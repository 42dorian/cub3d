/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:40 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/10 23:45:06 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*map_parsing(int args, char **argv)
{
	int		exit_code;
	t_map	*game_board;
	char	**read_file;
	const char *file_name;
	
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
		return (clean_up_2d(read_file), NULL);
	clean_up_2d(read_file);
	if (!map_is_valid(game_board->map, &exit_code))
		return (t_map_clean_up(game_board),
			print_invalid_map_message(exit_code), NULL);
	return (game_board);
}

void	init_player(t_player *player, int row, int column, char pos)
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

void	print_player_position(t_map *map, t_player *player)
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

static void	key_hook(t_cub *game)
{
	if (game->keys.a_key == 1)
		move_sideways(game, A_KEY);
	if (game->keys.d_key == 1)
		move_sideways(game, D_KEY);
	if (game->keys.w_key == 1)
		move_forward(game, W_KEY);
	if (game->keys.s_key == 1)
		move_forward(game, S_KEY);
	if (game->keys.left_key == 1)
		rotate_player(game, LEFT_KEY);
	if (game->keys.right_key == 1)
		rotate_player(game, RIGHT_KEY);
}

static int	render_loop(t_cub *game)
{
	key_hook(game);
	render_frame(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.img_ptr, 0, 0);
	return (0);
}

int	main(int args, char **argv)
{
	t_cub	game;

	ft_bzero(&game, sizeof(game));
	game.map = map_parsing(args, argv);
	if (!game.map)
		return (1);
	else
		t_map_clean_up(game.map);
	return (0);
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
	game.mlx.addr = mlx_get_data_addr(game.mlx.img_ptr, &game.mlx.bpp,
			&game.mlx.line_len, &game.mlx.endian);
	if (!game.mlx.addr)
		return (1);
	if (!load_images(&game))
		return (1);
	mlx_loop_hook(game.mlx.mlx_ptr, render_loop, &game);
	mlx_hook(game.mlx.win_ptr, 2, 1L << 0, key_down, &game);
	mlx_hook(game.mlx.win_ptr, 3, 1L << 1, key_up, &game);
	mlx_do_key_autorepeatoff(game.mlx.mlx_ptr);
	mlx_loop(game.mlx.mlx_ptr);
	t_map_clean_up(game.map);
	return (0);
}
