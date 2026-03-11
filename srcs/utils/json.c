/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:38:03 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 22:54:36 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "file_read.h"
#include "json.h"

int	get_sign(FILE *stream)
{
	int	sign;

	sign = 1;
	if (peek(stream) == '+' || peek(stream) == '-')
	{
		if (accept(stream, '-'))
			sign = -sign;
		else
			getc(stream);
	}
	return (sign);
}

float	ft_fatof(FILE *stream)
{
	float	nbr;
	float	dec;
	int		sign;

	nbr = 0;
	while (accept_set(stream, "\n\t\r "))
		;
	sign = get_sign(stream);
	while (ft_isdigit(peek(stream)))
	{
		if (!nbr && accept(stream, '0'))
			break ;
		nbr = nbr * 10 + (getc(stream) - '0');
	}
	if (!accept(stream, '.') || (!ft_isdigit(peek(stream)) && ungetc('.',
				stream)))
		return (nbr * sign);
	dec = 0.1;
	while (ft_isdigit(peek(stream)))
	{
		nbr += (getc(stream) - '0') * dec;
		dec /= 10;
	}
	return (nbr * sign);
}

char	*get_string(FILE *stream, t_parsing_data *p_data, t_global_data *g_data)
{
	char	*string;
	int		i;
	int		j;

	j = 1;
	string = ft_calloc(1, 512);
	if (!string)
		return (ft_perror(NULL, g_data->prog_name), NULL);
	i = 0;
	while (peek(stream) != '"' && peek(stream) != EOF)
	{
		if (accept(stream, '\\'))
		{
			if (peek(stream) != '"' && peek(stream) != '\\')
				(free(string), unexpected(stream, p_data, g_data));
		}
		string[i++] = getc(stream);
		if (i == (512 * ++j) - 1)
			string = ft_realloc(string, (j - 1) * 512, j * 512);
	}
	if (!accept(stream, '"'))
		(free(string), unexpected(stream, p_data, g_data));
	return (string);
}

void	free_json(t_json token)
{
	size_t	j;

	if (token.e_type == _brace)
	{
		j = -1;
		while (++j < token.u_data.s_brace.size)
		{
			free(token.u_data.s_brace.data[j].key);
			free_json(token.u_data.s_brace.data[j].value);
		}
		free(token.u_data.s_brace.data);
	}
	else if (token.e_type == _string)
		free(token.u_data.str);
}
