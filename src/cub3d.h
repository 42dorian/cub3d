/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:34 by dabdulla          #+#    #+#             */
/*   Updated: 2026/10/15 12:37:15 by bguhty           ###   ########.fr       */
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

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "../include/libft/libft.h"
# include "../include/get_next_line/get_next_line.h"

typedef struct	s_map t_map;
typedef struct s_mlx t_mlx;
typedef struct s_player t_player;
typedef struct s_ray t_ray;

typedef struct	s_map
{
	char		*SO;
	char		*EA;
	char		*NO;
	char		*WE;
	int			*ceiling;
	int			*floor;
	char		**map;
}				t_map;

typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *addr;
	int bpp;
	int line_len;
	int endian;
} t_mlx;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double cam_x;
	double cam_y;

}				t_player;

typedef struct s_ray
{
	int side;
	int step_x;
	int step_y;
	int map_x;
	int map_y;
	double perp_dist;
	double ray_x;
	double ray_y;
	double delta_x;
	double delta_y;
	double side_x;
	double side_y;

}			t_ray;

typedef struct	s_cub
{
	t_map		*map;
	t_mlx		mlx;
	t_player	player;
	t_ray		ray;
}				t_cub;

int 	is_white_space(char letter);
int 	map_len(char **map);
void    convert_spaces_to_zeroes(char **map);
int 	characters_check(char **map, int *exit_code);
int     get_len_of_read_file(char **read_file);
int 	is_null_terminator(char letter);
t_map   *creating_t_cub_struct(char **read_file);
char    **parsing_from_file(const char *file);
char    *normal_copy(char *original);
int     get_map_len(char **read_file);
int     flood_fill(char **map, int x, int y);
char    **copy_map(char **old_map);
int     is_safe_spot(char letter);
int     is_new_line(char letter);
int     get_first_map_len(char **read_file);
int     get_second_map_len(char **read_file);
void    display_invalid_map_message(int exit_code);
int		map_is_valid(char **map, int *exit_code);
void    split_clean_up(char **split_line);
int     get_last_index(char **read_file);
void render_frame(t_cub *game);
void put_color(t_mlx *mlx);
#endif
