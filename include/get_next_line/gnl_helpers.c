/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulla <dabdulla@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 15:35:41 by dabdulla          #+#    #+#             */
/*   Updated: 2026/11/11 15:40:10 by dabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_and_null(char **s, int *exit_code)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	*exit_code = 1;
	return (NULL);
}

char	*valid_free_and_null(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (NULL);
}

void	assign_exitcode(int *exit_code, int code)
{
	*exit_code = code;
}
