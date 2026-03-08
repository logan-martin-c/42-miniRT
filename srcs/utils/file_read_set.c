/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:47:07 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 23:08:38 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "file_read.h"

int	accept_set(FILE *stream, char *set)
{
	if (ft_isinset(peek(stream), set))
	{
		getc(stream);
		return (1);
	}
	return (0);
}

int	expect_set(FILE *stream, char *set, t_parsing_data *p_data,
		t_global_data *g_data)
{
	if (accept_set(stream, set))
		return (1);
	return (unexpected(stream, p_data, g_data));
}

char	*get_token_name(char c)
{
	if (c == '\n')
		return ("newline");
	if (c == '\t')
		return ("horizontal tab");
	if (c == '\r')
		return ("carriage return");
	return (NULL);
}
