/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:34 by dabdulla          #+#    #+#             */
/*   Updated: 2026/10/08 16:29:20 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define E 68
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

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../include/libft/libft.h"
# include "../include/get_next_line/get_next_line.h"

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

// all structs u create go here, my idea was that we don't have to allocate a lot of memory in this program
// so we can just assign values initially and work with that.
typedef struct	s_cub
{
	t_map		map;
}				t_cub;


int 	is_white_space(char letter);
int 	map_len(char **map);
void    convert_spaces_to_zeroes(char **map);

#endif
