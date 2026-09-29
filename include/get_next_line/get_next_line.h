/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:09:57 by dabdulla          #+#    #+#             */
/*   Updated: 2025/11/04 13:23:06 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 41
# endif

char	*get_next_line(int fd);
char	*read_loop(int fd, char *file);
int		is_newline(char *s);
int		find_new_line(char *str);
char	*join_free(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*free_and_null(char **s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *src);
int		ft_strlen(const char *s);

#endif
