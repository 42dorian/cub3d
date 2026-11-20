/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:40 by dabdulla          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/11/18 13:17:33 by bguhty           ###   ########.fr       */
=======
/*   Updated: 2026/11/11 16:41:11 by dabdulla         ###   ########.fr       */
>>>>>>> 73dea8cff245de9ec6ebfb47c1d09d245aa5b7dc
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		valid_file_type(char *file_name)
{
	int len;

	len = ft_strlen(file_name);
	if (file_name[len - 1] != B && file_name[len - 2] != U && file_name[len - 3] != C && file_name[len - 4] != DOT)
		return (0);
	return (1);
}

t_map	*map_parsing(int args, char **argv)
{
<<<<<<< HEAD
	int		exit_code;
	t_map	*game_board;
	char	**read_file;
	
=======
	int			exit_code;
	t_map		*game_board;
	char		**read_file;
	const char	*file_name;

	file_name = "cub_test.txt";
	(void)argv;
>>>>>>> 73dea8cff245de9ec6ebfb47c1d09d245aa5b7dc
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
<<<<<<< HEAD
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
	mlx_hook(game.mlx.win_ptr, 17, 0, mlx_loop_end, game.mlx.mlx_ptr);
	mlx_do_key_autorepeatoff(game.mlx.mlx_ptr);
	mlx_loop(game.mlx.mlx_ptr);
=======
	find_player(game.map, &game.player);
	if (!init_mlx(&game) || !load_images(&game))
		return (clean_game(&game), 1);
	mlx_hooks(&game);
>>>>>>> 73dea8cff245de9ec6ebfb47c1d09d245aa5b7dc
	clean_game(&game);
	return (0);
}
