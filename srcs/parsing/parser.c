/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:48:12 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/26 14:46:07 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_line(t_parsing_data *p_data, char *obj_line,
		t_global_data *g_data)
{
	t_obj_type	type;

	type = get_obj_type(obj_line);
	if (type == _obj_param)
		parse_params(p_data, obj_line, g_data);
	else if (type == _obj_object)
		parse_object(p_data, obj_line, g_data);
	else
	{
		printf("%d\n", type);
		ft_maperror("Invalid object type", p_data->line_nb, g_data->prog_name);
		(free(obj_line), clean_exit(1, g_data, p_data, NULL));
		exit(EXIT_FAILURE);
	}
}

int	parse_map(t_global_data *g_data, t_parsing_data *p_data)
{
	char	*obj_line;

	p_data->line_nb = 1;
	obj_line = "";
	while (obj_line)
	{
		obj_line = get_next_line(p_data->map_fd);
		if (!obj_line)
			return (0);
		if (obj_line[ft_strlen(obj_line) - 1] == '\n')
			obj_line[ft_strlen(obj_line) - 1] = '\0';
		parse_line(p_data, obj_line, g_data);
		free(obj_line);
		++p_data->line_nb;
	}
	return (0);
}

void	parse_rt(char *av[], t_global_data *g_data, t_parsing_data *p_data)
{
	p_data->map_fd = open_map(av[1], g_data->prog_name);
	parse_map(g_data, p_data);
	close(p_data->map_fd);
	p_data->map_fd = -1;
	if (DEBUG)
		print_objects(p_data, &g_data->world);
	if (lst_map_to_array(p_data, &g_data->world))
	{
		ft_perror(NULL, g_data->prog_name);
		clean_exit(1, g_data, p_data, NULL);
	}
}

void	parser(int ac, char *av[], t_global_data *g_data,
		t_parsing_data *p_data)
{
	check_args(ac, av, g_data->prog_name, &p_data->file_type);
	if (p_data->file_type == _rt)
		parse_rt(av, g_data, p_data);
	else if (p_data->file_type == _json)
		parse_json(av, g_data, p_data);
	clean_parsing(p_data);
}
