/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:40 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/09 13:27:08 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	read_file = parsing_from_file(argv[1]);
	if (!read_file)
		return (NULL);
	game_board = creating_t_cub_struct(read_file);
	if (!game_board)
		return (NULL);
	split_clean_up(read_file);
	if (!map_is_valid(game_board->map, &exit_code))
		return (t_map_clean_up(game_board),
			display_invalid_map_message(exit_code), NULL);
	return (game_board);
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

int init_mlx(t_cub *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (0);
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!game->mlx.win_ptr)
		return (0);
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr, WIDTH, HEIGHT);
	if (!game->mlx.img_ptr)
		return (0);
	game->mlx.addr = mlx_get_data_addr(game->mlx.img_ptr, &game->mlx.bpp,
			&game->mlx.line_len, &game->mlx.endian);
	if (!game->mlx.addr)
		return (0);
	return (1);
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
	mlx_loop_hook(game.mlx.mlx_ptr, render_loop, &game);
	mlx_hook(game.mlx.win_ptr, 2, 1L << 0, key_down, &game);
	mlx_hook(game.mlx.win_ptr, 3, 1L << 1, key_up, &game);
	mlx_hook(game.mlx.win_ptr, 17, 0, mlx_loop_end, game.mlx.mlx_ptr);
	mlx_do_key_autorepeatoff(game.mlx.mlx_ptr);
	mlx_loop(game.mlx.mlx_ptr);
	clean_game(&game);
	return (0);
}
