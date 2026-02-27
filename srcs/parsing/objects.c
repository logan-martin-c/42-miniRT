/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:51:26 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/26 14:44:50 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	new_sphere(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	char	**params;

	params = ft_split_charset(obj_line, " \t\v\f\r");
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
			&node->color))
		return (ft_free_strs(params),
			ft_maperror("u_data.sphere : invalid parameters", p_data->line_nb,
				g_data->prog_name));
	node->u_data.sphere.radius = node->u_data.sphere.diameter / 2;
	if (params[4])
		node->u_data.sphere.reflectance = ft_atof(params[4]);
	else
		node->u_data.sphere.reflectance = 0;
	if (params[5])
		node->u_data.sphere.refraction = ft_atof(params[5]);
	else
		node->u_data.sphere.refraction = 1;
	node->rot = (t_vect3){0, 0, -1};
	node->e_type = _sphere;
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	return (ft_free_strs(params), 0);
}

int	new_plane(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	char	**params;

	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!params)
	{
		free(node);
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data, NULL);
	}
	if (!params[1] || !params[2] || !params[3] || params[4])
		return (ft_free_strs(params), ft_maperror("plane : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	if (parse_pos(params[1], &node->pos, 0) || parse_pos(params[2], &node->rot,
			1) || parse_raw_color(params[3], &node->color))
		return (ft_free_strs(params), ft_maperror("plane : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	node->e_type = _plane;
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	return (ft_free_strs(params), 0);
}

int	new_cylinder(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	char	**params;

	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!params)
	{
		free(node);
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data, NULL);
	}
	if (check_args_count(params, 6, 6) == -1)
		return (ft_free_strs(params),
			ft_maperror("cylinder : invalid parameters", p_data->line_nb,
				g_data->prog_name));
	if (parse_pos(params[1], &node->pos, 0) || parse_pos(params[2], &node->rot,
			1) || parse_float(params[3], &node->u_data.cylinder.diameter)
		|| parse_float(params[4], &node->u_data.cylinder.height)
		|| parse_raw_color(params[5], &node->color))
		return (ft_free_strs(params),
			ft_maperror("cylinder : invalid parameters", p_data->line_nb,
				g_data->prog_name));
	node->e_type = _cylinder;
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
	if (check_args_count(params, 4, 4) == -1)
		return (ft_free_strs(params), ft_maperror("light : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	if (parse_pos(params[1], &node->u_data.light.pos, 0)
		|| !ft_isfloat_str(params[2]) || parse_raw_color(params[3],
			&node->u_data.light.color))
		return (ft_free_strs(params), ft_maperror("light : invalid parameters",
				p_data->line_nb, g_data->prog_name));
	node->u_data.light.ratio = ft_atof(params[2]);
	if (node->u_data.light.ratio > 1 || node->u_data.light.ratio < 0)
		return (ft_free_strs(params), ft_maperror("light : invalid ratio",
				p_data->line_nb, g_data->prog_name));
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
	if (!ft_strncmp(obj_line, "sp", 2) && ft_isspace(obj_line[2]))
		ret = new_sphere(p_data, obj_line, g_data, node);
	else if (!ft_strncmp(obj_line, "pl", 2) && ft_isspace(obj_line[2]))
		ret = new_plane(p_data, obj_line, g_data, node);
	else if (!ft_strncmp(obj_line, "cy", 2) && ft_isspace(obj_line[2]))
		ret = new_cylinder(p_data, obj_line, g_data, node);
	else if (!ft_strncmp(obj_line, "L", 1) && ft_isspace(obj_line[1]))
		ret = new_light(p_data, obj_line, g_data, node);
	if (ret)
		(free(obj_line), free(node), clean_exit(1, g_data, p_data, NULL));
	p_data->obj_count++;
}
