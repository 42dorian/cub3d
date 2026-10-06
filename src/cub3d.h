/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 15:18:34 by dabdulla          #+#    #+#             */
/*   Updated: 2026/09/29 15:18:36 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include "../include/libft/libft.h"
# include "../include/get_next_line/get_next_line.h"

typedef struct	s_map
{

}				t_map;

// all structs u create go here, my idea was that we don't have to allocate a lot of memory in this program
// so we can just assign values initially and work with that.
typedef struct	s_cub
{
	t_map		map;
}				t_cub;

#endif
