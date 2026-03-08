/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:37:48 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 22:36:08 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "file_read.h"
#include "json.h"

int	new_pair(t_pair **pair, int *brace_size, t_parsing_data *p_data,
		t_global_data *g_data)
{
	char	*string;
	int		sub_node_count;

	sub_node_count = 0;
	skip_whitespaces(p_data->stream, &p_data->line_nb);
	if (!expect(p_data->stream, '"', p_data, g_data))
		return (1);
	string = get_string(p_data->stream, p_data, g_data);
	if (!string)
		return (1);
	skip_whitespaces(p_data->stream, &p_data->line_nb);
	if (!expect(p_data->stream, ':', p_data, g_data))
		return (free(string), 1);
	*pair = ft_realloc(*pair, *brace_size * sizeof(t_pair), (*brace_size + 1)
			* sizeof(t_pair));
	if (!*pair)
		return (free(string), 1);
	pair[0][*brace_size].key = string;
	if (lexer(&pair[0][(*brace_size)++].value, &sub_node_count, p_data, g_data))
		return (1);
	return (0);
}

int	new_brace(t_json *dest, int *node_count, t_parsing_data *p_data,
		t_global_data *g_data)
{
	int		brace_size;
	t_pair	*pair;

	brace_size = 0;
	pair = NULL;
	dest[*node_count].e_type = _brace;
	while (peek(p_data->stream) != '}' && peek(p_data->stream) != EOF)
	{
		if ((brace_size && !expect(p_data->stream, ',', p_data, g_data))
			|| new_pair(&pair, &brace_size, p_data, g_data))
		{
			dest[*node_count].e_type = _brace;
			dest[*node_count].u_data.s_brace.data = pair;
			dest[(*node_count)++].u_data.s_brace.size = brace_size;
			return (1);
		}
		skip_whitespaces(p_data->stream, &p_data->line_nb);
	}
	dest[*node_count].u_data.s_brace.data = pair;
	dest[(*node_count)++].u_data.s_brace.size = brace_size;
	return (!expect(p_data->stream, '}', p_data, g_data));
}

int	new_float(t_json *dest, int *node_count, t_parsing_data *p_data,
		t_global_data *g_data)
{
	(void)g_data;
	dest[(*node_count)].e_type = _float;
	dest[*node_count++].u_data.num = ft_fatof(p_data->stream);
	return (0);
}

int	new_string(t_json *dest, int *node_count, t_parsing_data *p_data,
		t_global_data *g_data)
{
	dest[(*node_count)].e_type = _string;
	dest[*node_count].u_data.str = get_string(p_data->stream, p_data, g_data);
	if (!dest[*node_count++].u_data.str)
		return (1);
	return (0);
}

int	new_array(t_json *dest, int *node_count, t_parsing_data *p_data,
		t_global_data *g_data)
{
	int	i;

	i = -1;
	while (++i < 4 && peek(p_data->stream) != ']')
	{
		dest[*node_count].e_type = _array;
		if ((i && !expect(p_data->stream, ',', p_data, g_data)))
			return (1);
		skip_whitespaces(p_data->stream, &p_data->line_nb);
		if (!ft_isdigit(peek(p_data->stream)) && peek(p_data->stream) != '-')
			return (!unexpected(p_data->stream, p_data, g_data));
		dest[*node_count].u_data.array[i] = ft_fatof(p_data->stream);
		skip_whitespaces(p_data->stream, &p_data->line_nb);
		if (i == 2 && peek(p_data->stream) == ']')
		{
			++i;
			break ;
		}
	}
	if (!expect(p_data->stream, ']', p_data, g_data))
		return (1);
	dest[*node_count++].size = i;
	return (0);
}
