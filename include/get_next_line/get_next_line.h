/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguhty <bguhty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:09:57 by dabdulla          #+#    #+#             */
/*   Updated: 2026/10/07 16:43:15 by bguhty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 41
# endif

char	*get_next_line(int fd, int *exit_code);
char	*read_loop(int fd, char *file);
int		is_newline(char *s);
int		find_new_line(char *str);
char	*join_free(char *s1, char *s2);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char	*free_and_null(char **s, int *exit_code);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strdup_gnl(char *src);
int		ft_strlen_gnl(const char *s);


#endif
