/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:34 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/11 15:16:06 by bguhty           ###   ########.fr       */
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
	char				*so;
	char				*ea;
	char				*no;
	char				*we;
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
void					convert_spaces_to_zeroes(char **map);
int						player_check(char **map, int *exit_code);
int						is_null_terminator(char letter);
t_map					*creating_t_cub_struct(char **read_file);
char					**parsing_from_file(const char *file);
char					*normal_copy(char *original);
int						flood_fill(char **map, int x, int y);
char					**copy_map(char **old_map);
char					**get_map(char **read_file);
int						is_safe_spot(char letter);
int						check_missing_textures(t_map *map_struct);
int						*get_levels(char **read_file, const char letter);
int						matching_levels(char *current_line, const char letter);
void					free_map_with_index(char **map, int last, int current);
int						get_first_map_len(char **read_file);
void					print_invalid_map_message(int exit_code);
int						map_is_valid(char **map, int *exit_code);
void					clean_up_2d(char **split_line);
int						*get_colour(char *line);
char					*get_texture(char *line);
int						allocate_colours_and_split_line(int **colours,
							char ***split_line, char *line);
int						add_colours_to_array(int *colours,
							char **split_colours);
char					*get_direction(char **read_file, const char *direction);
int						matching_names(char *current_line, char *direction);
int						get_last_index_of_map(char **read_file);
void					render_frame(t_cub *game);
void					print_missing_level_id(const char id);
void					print_missing_texture_pack(char *level);
void					print_multiple_texture_packs(char *level);
void					print_missing_id_error(const char *id);
void					print_colour_code_error(void);
void					t_map_clean_up(t_map *game_board);
void					find_player(t_map *map, t_player *player);
void					init_player(t_player *player, int row, int column,
							char pos);
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
void					put_pixel(t_mlx *mlx, int row, int col, int color);
void					put_color(t_mlx *mlx);
void					init_rays(t_cub *game, int x);
void					init_step_and_side(t_cub *game);

int						is_player(char letter);
int						is_null_terminator(char letter);
int						is_white_space(char letter);
int						is_wall(char letter);
int						get_map_len_from_file(char **read_file);
int						get_y_of_start(char **map);
int						get_x_of_start(char **map);
int						get_struct_values(t_map *map_struct, char **read_file);
int						is_valid_input(char **read_file);
int						get_2d_len(char **split_line);
int						get_len_of_file(const char *file, int *exit_code);
void					set_east(t_player *player);
void					set_west(t_player *player);
void					set_south(t_player *player);
void					set_north(t_player *player);

#endif
