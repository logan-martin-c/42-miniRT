/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:48:12 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 19:16:31 by lomartin         ###   ########.fr       */
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
		ft_maperror("Invalid object type", g_data->prog_name);
		(free(obj_line), clean_exit(1, g_data, p_data));
		exit(EXIT_FAILURE);
	}
}

int	parse_map(t_global_data *g_data, t_parsing_data *p_data)
{
	char	*obj_line;

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
	}
	return (0);
}

void	lst_map_to_array(t_parsing_data *p_data, t_world_data *world)
{
	t_list	*next;
	int		i;

	world->objs = malloc(sizeof(t_object) * (p_data->obj_count + 1));
	i = -1;
	while (++i < p_data->obj_count)
	{
		world->objs[i] = *(t_object *)p_data->obj_lst->content;
		next = p_data->obj_lst->next;
		free_node(p_data->obj_lst->content);
		free(p_data->obj_lst);
		p_data->obj_lst = next;
	}
}

void	parser(int ac, char *av[], t_global_data *g_data,
		t_parsing_data *p_data)
{
	check_args(ac, av, g_data->prog_name);
	p_data->map_fd = open_map(av[1], g_data->prog_name);
	parse_map(g_data, p_data);
	close(p_data->map_fd);
	p_data->map_fd = -1;
	if (DEBUG)
		print_objects(p_data, &g_data->world);
	lst_map_to_array(p_data, &g_data->world);
	ft_lstclear(&p_data->obj_lst, free_node);
}
