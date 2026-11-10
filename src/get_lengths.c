/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lengths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 12:42:37 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/10 13:31:41 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_len_of_file(const char *file, int *exit_code)
{
	char	*curr;
	int		fd;
	int		len;

	len = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (1)
	{
		curr = get_next_line(fd, exit_code);
		if (!curr)
			break ;
		len++;
		free(curr);
	}
	close(fd);
	if (*exit_code)
		return (-1);
	return (len);
}

int	get_map_len_from_file(char **read_file)
{
	int	last_index;
	int	len;

	len = 0;
	last_index = get_last_index_of_map(read_file);
	while (ft_strncmp(read_file[last_index--], "", 1))
		len++;
	return (len);
}
