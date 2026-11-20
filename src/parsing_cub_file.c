/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:06:16 by bguhty            #+#    #+#             */
/*   Updated: 2026/11/20 19:28:44 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_lines_from_file(const char *file, char **lines, int *exit_code)
{
	int	fd;
	int	i;

	fd = 0;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		*exit_code = 1;
		return ;
	}
	while (1)
	{
		lines[i] = get_next_line(fd, exit_code);
		if (*exit_code)
			break ;
		if (!lines[i])
			break ;
		i++;
	}
	close(fd);
}

char	**parsing_from_file(const char *file)
{
	int		len;
	int		exit_code;
	char	**lines;

	exit_code = 0;
	len = get_len_of_file(file, &exit_code);
	if (len == -1)
	{
		write(2, "Error\nWrong file\n", 17);
		return (NULL);
	}
	if (len == 0)
	{
		write(2, "Error\nEmpty file!\n", 18);
		return (NULL);
	}
	lines = ft_calloc(sizeof(char *), len + 1);
	if (!lines)
		return (NULL);
	get_lines_from_file(file, lines, &exit_code);
	if (exit_code)
		return (clean_up_2d(lines), NULL);
	return (lines);
}

int	get_valid_lines(char **read_file)
{
	int	valid_lines;
	int	i;

	i = 0;
	valid_lines = 0;
	while (read_file[i])
	{
		if (ft_strncmp(read_file[i], "", 1))
			valid_lines++;
		i++;
	}
	return (valid_lines);
}

int	trim_the_read_file(char **read_file)
{
	int		i;
	char	*set;
	int		end_index;

	i = 0;
	end_index = get_2d_len(read_file) - get_first_map_len(read_file);
	set = create_white_space_set();
	if (!set)
		return (clean_up_2d(read_file), 0);
	while (i < end_index)
	{
		read_file[i] = ft_strtrim(read_file[i], set);
		if (!read_file[i])
		{
			clean_up_2d(read_file);
			return (free(set), 0);
		}
		i++;
	}
	free(set);
	if (get_valid_lines(read_file) < 7)
		return (clean_up_2d(read_file), write(2,
				"Error\nNot enough info specified in file!\n", 41), 0);
	return (1);
}

char	**trim_empty_lines(char **read_file)
{
	char	**trimmed_read_line;
	int		trimmed_len;
	int		i;
	int		trimmed_index;

	i = -1;
	trimmed_index = 0;
	trimmed_len = get_trimmed_len(read_file);
	trimmed_read_line = ft_calloc(sizeof(char *), trimmed_len + 2);
	if (!trimmed_read_line)
		return (NULL);
	while (trimmed_index <= trimmed_len)
	{
		if (ft_strncmp(read_file[++i], "", 1))
			trimmed_read_line[trimmed_index++] = normal_copy(read_file[i]);
		if (trimmed_index > 0 && !trimmed_read_line[trimmed_index - 1])
			return (NULL);
		if (trimmed_index == 6)
			trimmed_read_line[trimmed_index++] = ft_strdup("");
	}
	clean_up_2d(read_file);
	trimmed_read_line[trimmed_index] = NULL;
	return (trimmed_read_line);
}
