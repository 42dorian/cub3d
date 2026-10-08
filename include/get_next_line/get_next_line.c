/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:09:55 by dabdulla          #+#    #+#             */
/*   Updated: 2026/10/08 21:37:03 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*join_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin_gnl(s1, s2);
	if (!tmp)
		return (NULL);
	return (tmp);
}

int	find_new_line(char *str)
{
	int	i;

	i = 0;
	if (*str == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

int	is_newline(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*read_loop(int fd, char *file)
{
	char	*buffer;
	int		r;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_and_null(&file, &r));
	if (!file)
	{
		file = malloc(1);
		if (!file)
			return (free_and_null(&buffer, &r));
		file[0] = '\0';
	}
	r = 1;
	while (r > 0 && !is_newline(file))
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r <= 0)
			break ;
		buffer[r] = '\0';
		file = join_free(file, buffer);
	}
	return (free_and_null(&buffer, &r), file);
}

char	*get_next_line(int fd, int *exit_code)
{
	static char	*file;
	char		*tmp;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_and_null(&file, exit_code));
	file = read_loop(fd, file);
	if (!file)
		return (NULL);
	if (*file == '\0')
		return (valid_free_and_null(&file));
	tmp = ft_substr_gnl(file, 0, find_new_line(file));
	if (!tmp)
		return (free_and_null(&file, exit_code));
	str = ft_substr_gnl(file, find_new_line(tmp), ft_strlen_gnl(file)
			- ft_strlen_gnl(tmp));
	valid_free_and_null(&file);
	if (!str)
		return (free_and_null(&tmp, exit_code));
	file = ft_strdup_gnl(str);
	valid_free_and_null(&str);
	if (!file)
		return (free_and_null(&file, exit_code), free_and_null(&tmp, exit_code));
	return (tmp);
}
