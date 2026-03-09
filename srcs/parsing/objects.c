/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:51:26 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/09 11:51:39 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	new_sphere(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	char	**params;

	params = ft_split_charset(obj_line, " \t\v\f\r");
	(node->e_type = _sphere, set_default_obj(node));
	if (!params)
	{
		free(node);
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data, NULL);
	}
	if (check_args_count(params, 4, 6) == -1)
		return (ft_free_strs(params), ft_maperror("sphere : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	if (parse_pos(params[1], &node->pos, 0) || parse_float(params[2],
			&node->u_data.sphere.diameter) || parse_raw_color(params[3],
			&node->material.color))
		return (ft_free_strs(params),
			ft_maperror("u_data.sphere : invalid parameters", p_data->line_nb,
				g_data->prog_name));
	node->u_data.sphere.radius = node->u_data.sphere.diameter / 2;
	if (params[4])
		node->material.tex_name = ft_strdup(params[4]);
	if (params[4] && params[5])
		node->material.normal_name = ft_strdup(params[5]);
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	return (ft_free_strs(params), 0);
}

int	new_plane(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	char	**params;

	params = ft_split_charset(obj_line, " \t\v\f\r");
	set_default_obj(node);
	if (!params)
	{
		free(node);
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data, NULL);
	}
	if (check_args_count(params, 4, 6) == -1)
		return (ft_free_strs(params), ft_maperror("sphere : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	if (parse_pos(params[1], &node->pos, 0) || parse_pos(params[2], &node->rot,
			1) || parse_raw_color(params[3], &node->material.color))
		return (ft_free_strs(params), ft_maperror("plane : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	node->e_type = _plane;
	if (params[4])
		node->material.tex_name = ft_strdup(params[4]);
	if (params[4] && params[5])
		node->material.normal_name = ft_strdup(params[5]);
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	return (ft_free_strs(params), 0);
}

int	new_cylinder(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	char	**params;

	params = ft_split_charset(obj_line, " \t\v\f\r");
	(node->e_type = _cylinder, set_default_obj(node));
	if (!params)
		(free(node), clean_exit(ft_perror(NULL, g_data->prog_name), g_data,
				p_data, NULL));
	if (check_args_count(params, 6, 8) == -1)
		return (ft_free_strs(params),
			ft_maperror("cylinder : invalid parameters", p_data->line_nb,
				g_data->prog_name));
	if (parse_pos(params[1], &node->pos, 0) || parse_pos(params[2], &node->rot,
			1) || parse_float(params[3], &node->u_data.cylinder.radius)
		|| parse_float(params[4], &node->u_data.cylinder.height)
		|| parse_raw_color(params[5], &node->material.color))
		return (ft_free_strs(params),
			ft_maperror("cylinder : invalid parameters", p_data->line_nb,
				g_data->prog_name));
	node->u_data.cylinder.radius *= 0.5;
	if (params[6])
		node->material.tex_name = ft_strdup(params[6]);
	if (params[6] && params[7])
		node->material.normal_name = ft_strdup(params[7]);
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	return (ft_free_strs(params), 0);
}

int	new_light(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	char	**params;

	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!params)
		return (ft_perror(NULL, g_data->prog_name));
	if (check_args_count(params, 4, 5) == -1)
		return (ft_free_strs(params), ft_maperror("light : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	if (parse_pos(params[1], &node->pos, 0) || !ft_isfloat_str(params[2])
		|| parse_raw_color(params[3], &node->material.color))
		return (ft_free_strs(params), ft_maperror("light : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	node->u_data.light.ratio = ft_atof(params[2]);
	if (node->u_data.light.ratio > 1 || node->u_data.light.ratio < 0)
		return (ft_free_strs(params), ft_maperror("light : invalid ratio",
				p_data->line_nb, g_data->prog_name));
	node->u_data.light.radius = 0;
	if (params[4])
		node->u_data.light.radius = ft_atof(params[4]);
	node->e_type = _light;
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	p_data->light_count++;
	return (ft_free_strs(params), 0);
}

void	parse_object(t_parsing_data *p_data, char *obj_line,
		t_global_data *g_data)
{
	t_object	*node;
	int			ret;

	ret = 1;
	node = malloc(sizeof(t_object));
	if (!node)
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data, NULL);
	ft_bzero(node, sizeof(t_object));
	if (!ft_strncmp(obj_line, "sp", 2) && ft_isspace(obj_line[2]))
		ret = new_sphere(p_data, obj_line, g_data, node);
	else if (!ft_strncmp(obj_line, "pl", 2) && ft_isspace(obj_line[2]))
		ret = new_plane(p_data, obj_line, g_data, node);
	else if (!ft_strncmp(obj_line, "cy", 2) && ft_isspace(obj_line[2]))
		ret = new_cylinder(p_data, obj_line, g_data, node);
	else if (!ft_strncmp(obj_line, "co", 2) && ft_isspace(obj_line[2]))
		ret = new_cone(p_data, obj_line, g_data, node);
	else if (!ft_strncmp(obj_line, "L", 1) && ft_isspace(obj_line[1]))
		ret = new_light(p_data, obj_line, g_data, node);
	if (ret)
		(free(obj_line), free(node), clean_exit(1, g_data, p_data, NULL));
	p_data->obj_count++;
}
