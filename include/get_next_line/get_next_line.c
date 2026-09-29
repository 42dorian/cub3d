/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:09:55 by dabdulla          #+#    #+#             */
/*   Updated: 2025/11/06 16:38:59 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
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
		return (free_and_null(&file));
	if (!file)
	{
		file = malloc(1);
		if (!file)
			return (free_and_null(&buffer));
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
	return (free_and_null(&buffer), file);
}

char	*get_next_line(int fd)
{
	static char	*file;
	char		*tmp;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_and_null(&file));
	file = read_loop(fd, file);
	if (!file)
		return (NULL);
	if (*file == '\0')
		return (free_and_null(&file));
	tmp = ft_substr(file, 0, find_new_line(file));
	if (!tmp)
		return (free_and_null(&file));
	str = ft_substr(file, find_new_line(tmp), ft_strlen(file) - ft_strlen(tmp));
	free_and_null(&file);
	if (!str)
		return (free_and_null(&tmp));
	file = ft_strdup(str);
	free_and_null(&str);
	if (!file)
		return (free_and_null(&file), free_and_null(&tmp));
	return (tmp);
}

// #include "get_next_line_utils.c"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd;
	char *s;

	fd = open("test.txt", O_RDONLY);
	while ((s = get_next_line(fd)))
	{
		printf("%s", s);
		free_and_null(&s);
	}
	s = get_next_line(fd);
	printf("%s", s);
	free_and_null(&s);
	close(fd);
}