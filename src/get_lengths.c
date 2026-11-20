/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lengths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 12:42:37 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/20 19:21:48 by dabdulla         ###   ########.fr       */
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

char	*get_texture(char *line)
{
	char	*texture_path;
	char	**split_line;

	split_line = ft_split(line, SPACE);
	if (!split_line)
		return (NULL);
	if (get_2d_len(split_line) == 1)
	{
		print_missing_texture_pack(split_line[0]);
		clean_up_2d(split_line);
		return (NULL);
	}
	else if (get_2d_len(split_line) > 2)
	{
		print_multiple_texture_packs(split_line[0]);
		clean_up_2d(split_line);
		return (NULL);
	}
	texture_path = normal_copy(split_line[1]);
	clean_up_2d(split_line);
	return (texture_path);
}

int	get_2d_len(char **split_line)
{
	int	len;

	len = 0;
	while (split_line[len])
		len++;
	return (len);
}

int	get_trimmed_len(char **read_file)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (read_file[i])
	{
		if (ft_strncmp(read_file[i], "", 1))
			len++;
		i++;
	}
	return (len);
}
