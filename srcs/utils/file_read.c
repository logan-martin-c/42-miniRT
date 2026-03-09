/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:46:52 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/09 11:27:26 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "file_read.h"

int	peek(FILE *stream)
{
	int	c;

	c = getc(stream);
	ungetc(c, stream);
	return (c);
}

int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		getc(stream);
		return (1);
	}
	return (0);
}

int	unexpected(FILE *stream, t_parsing_data *p_data, t_global_data *g_data)
{
	char	c;
	char	*error;
	char	*token_name;

	c = peek(stream);
	if (c == EOF)
		error = ft_strdup("unexpected end of file");
	else
	{
		token_name = get_token_name(c);
		if (token_name)
			error = ft_strjoin_mult(3, "unexpected token '", token_name, "'");
		else
			error = ft_strjoin_mult(3, "unexpected token '",
					(char [2]){c, '\0'}, "'");
	}
	ft_maperror(error, p_data->line_nb, g_data->prog_name);
	free(error);
	return (0);
}

int	expect(FILE *stream, char c, t_parsing_data *p_data, t_global_data *g_data)
{
	if (accept(stream, c))
		return (1);
	return (unexpected(stream, p_data, g_data));
}

void	skip_whitespaces(FILE *stream, int *line_count)
{
	bool	ok;

	ok = true;
	while (ok)
	{
		if (peek(stream) == '\n')
			++(*line_count);
		ok = accept_set(stream, " \n\t\r");
	}
}
