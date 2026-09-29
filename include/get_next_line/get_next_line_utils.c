/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:09:53 by dabdulla          #+#    #+#             */
/*   Updated: 2025/11/04 13:23:11 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dupsrc;

	i = 0;
	dupsrc = malloc(ft_strlen(src) + 1);
	if (!dupsrc)
		return (NULL);
	while (src[i])
	{
		dupsrc[i] = src[i];
		i++;
	}
	dupsrc[i] = '\0';
	return (dupsrc);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_arr;

	i = 0;
	new_arr = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!new_arr)
		return (s1);
	while (s1[i])
	{
		new_arr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_arr[i] = s2[j];
		i++;
		j++;
	}
	if (s1)
		free(s1);
	new_arr[i] = '\0';
	return (new_arr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*free_and_null(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (NULL);
}
