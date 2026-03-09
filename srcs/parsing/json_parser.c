/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:38:35 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 22:36:32 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "debug.h"
#include "file_read.h"
#include "json.h"

int	lexer(t_json *dest, int *node_count, t_parsing_data *p_data,
		t_global_data *g_data)
{
	FILE	*stream;

	stream = p_data->stream;
	skip_whitespaces(p_data->stream, &p_data->line_nb);
	if (accept(stream, '{'))
		return (new_brace(dest, node_count, p_data, g_data));
	if (ft_isdigit(peek(stream)) || peek(stream) == '-')
		return (new_float(dest, node_count, p_data, g_data));
	if (accept(stream, '\"'))
		return (new_string(dest, node_count, p_data, g_data));
	if (accept(stream, '['))
		return (new_array(dest, node_count, p_data, g_data));
	if (expect(stream, EOF, p_data, g_data))
		return (0);
	return (1);
}

void	parse_json(char *av[], t_global_data *g_data, t_parsing_data *p_data)
{
	p_data->stream = fopen(av[1], "r");
	if (!p_data->stream)
	{
		ft_perror(av[1], g_data->prog_name);
		clean_exit(1, g_data, p_data, NULL);
	}
	p_data->line_nb = 1;
	while (peek(p_data->stream) != EOF)
	{
		if (lexer(&p_data->json, &p_data->node_count, p_data, g_data))
			clean_exit(1, g_data, p_data, NULL);
		skip_whitespaces(p_data->stream, &p_data->line_nb);
	}
	fclose(p_data->stream);
	p_data->stream = NULL;
	if (DEBUG)
		print_json(p_data->json, 0);
	if (json_to_array(p_data, g_data, &g_data->world))
		clean_exit(1, g_data, p_data, NULL);
}
