/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 12:32:51 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/10 23:53:01 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_missing_id_error(const char *id)
{
	write(2, "Error\nMissing ", 14);
	write(2, id, ft_strlen(id));
	write(2, " identifier\n", 12);
}

void	print_missing_texture_pack(char *level)
{
	write(2, "Error\n", 6);
	write(2, level, ft_strlen(level));
	write(2, " identifier\n", 12);
}

void	print_multiple_texture_packs(char *level)
{
	write(2, "Error\nMultiple texture packs for ", 33);
	write(2, level, ft_strlen(level));
	write(2, "\n", 1);
}

void    print_colour_code_error()
{
    write(2, "Error\nAll colours' codes must be", 32);
    write(2, " in the following range: 0-255\n", 31);
}

void	print_invalid_map_message(int exit_code)
{
	if (exit_code == 1)
		write(2, "Error\nMultiple starting positions!\n", 35);
	else if (exit_code == 2)
		write(2, "Error\nInvalid character on the board!\n", 38);
	else if (exit_code == 3)
		write(2, "Error\nAdditional island(s)!\n", 28);
	else if (exit_code == 4)
		write(2, "Error\nThe island is not completely surrounded by walls!\n",
			56);
	else if (exit_code == 5)
		write(2, "Error\nNo starting position spcified!\n", 37);
}

void	print_missing_level_id(const char id)
{
	write(2, "Error\nMissing ", 14);
	ft_putchar_fd(id, 2);
	write(2, " identifier\n", 12);
}
