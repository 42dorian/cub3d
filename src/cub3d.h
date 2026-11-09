/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:34 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/09 10:50:59 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define E 69
# define N 78
# define S 83
# define W 87
# define ZERO 48
# define COMMA 44
# define ONE 49
# define BACKSPACE 8
# define CARRIAGE_RET 13
# define SPACE 32
# define NULL_TERMINATOR 0
# define WIDTH 1280
# define HEIGHT 720
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ROTATE_SPEED 0.05
# define MOVE_SPEED 0.05
# define WALL_OFFSET 0.2

# include "../include/get_next_line/get_next_line.h"
# include "../include/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map	t_map;
typedef struct s_mlx	t_mlx;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_keys	t_keys;
typedef struct s_tex	t_tex;

typedef struct s_map
{
	char				*SO;
	char				*EA;
	char				*NO;
	char				*WE;
	int					*ceiling;
	int					*floor;
	char				**map;
}						t_map;

typedef struct s_mlx
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_mlx;

typedef struct s_tex
{
	void				*img;
	char				*addr;
	int					width;
	int					height;
	int					bpp;
	int					line_len;
	int					endian;
}						t_tex;

typedef struct s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				cam_x;
	double				cam_y;

}						t_player;

typedef struct s_keys
{
	int					w_key;
	int					s_key;
	int					a_key;
	int					d_key;
	int					left_key;
	int					right_key;
}						t_keys;

typedef struct s_ray
{
	int					side;
	int					step_x;
	int					step_y;
	int					map_x;
	int					map_y;
	double				perp_dist;
	double				ray_x;
	double				ray_y;
	double				delta_x;
	double				delta_y;
	double				side_x;
	double				side_y;

}						t_ray;

typedef struct s_cub
{
	t_map				*map;
	t_mlx				mlx;
	t_player			player;
	t_ray				ray;
	t_keys				keys;
	t_tex				tex[4];
}						t_cub;

int						is_white_space(char letter);
int						map_len(char **map);
void					convert_spaces_to_zeroes(char **map);
int						characters_check(char **map, int *exit_code);
int						get_len_of_read_file(char **read_file);
int						is_null_terminator(char letter);
t_map					*creating_t_cub_struct(char **read_file);
char					**parsing_from_file(const char *file);
char					*normal_copy(char *original);
int						get_map_len(char **read_file);
int						flood_fill(char **map, int x, int y);
char					**copy_map(char **old_map);
int						is_safe_spot(char letter);
int						is_new_line(char letter);
int						get_first_map_len(char **read_file);
int						get_second_map_len(char **read_file);
void					display_invalid_map_message(int exit_code);
int						map_is_valid(char **map, int *exit_code);
void					split_clean_up(char **split_line);
int						get_last_index(char **read_file);
void					render_frame(t_cub *game);
void					print_missing_texture_pack(char *level);
void					print_multiple_texture_packs(char *level);
void					t_map_clean_up(t_map *game_board);
void					find_player(t_map *map, t_player *player);
void					init_player(t_player *player, int row, int column, char pos);
void					move_sideways(t_cub *game, int keycode);
void					move_forward(t_cub *game, int keycode);
int						key_down(int keycode, t_cub *game);
int						key_up(int keycode, t_cub *game);
void					rotate_player(t_cub *game, int keycode);
t_tex					*tex_selector(t_cub *game);
int						get_tex_x(t_cub *game, t_tex *t);
int						get_texture_color(t_tex *t, int tex_x, int tex_y);
int						load_images(t_cub *g);
int						free_texture_paths(t_map *map_struct);
void					clean_game(t_cub *game);

#endif
