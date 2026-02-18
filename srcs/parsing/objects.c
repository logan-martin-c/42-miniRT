/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:51:26 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 19:15:43 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	new_sphere(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	t_sphere	*sphere;
	char		**params;

	sphere = malloc(sizeof(t_sphere));
	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!sphere || !params)
	{
		free(sphere);
		free(node);
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data);
	}
	if (check_args_count(params, 4, 4) == -1)
		return (free(sphere), ft_free_strs(params),
			ft_maperror("sphere : invalid parameters", g_data->prog_name));
	if (parse_pos(params[1], &sphere->pos, 0) || parse_float(params[2],
			&sphere->diameter) || parse_raw_color(params[3], &sphere->color))
		return (free(sphere), ft_free_strs(params),
			ft_maperror("sphere : invalid parameters", g_data->prog_name));
	sphere->radius = sphere->diameter / 2;
	node->e_type = _sphere;
	node->data = sphere;
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	return (ft_free_strs(params), 0);
}

int	new_plane(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	t_plane	*plane;
	char	**params;

	plane = malloc(sizeof(t_plane));
	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!plane || !params)
	{
		free(plane);
		free(node);
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data);
	}
	if (!params[1] || !params[2] || !params[3] || params[4])
		return (free(plane), ft_free_strs(params),
			ft_maperror("plane : invalid parameters", g_data->prog_name));
	if (parse_pos(params[1], &plane->pos, 0) || parse_pos(params[2],
			&plane->rot, 1) || parse_raw_color(params[3], &plane->color))
		return (free(plane), ft_free_strs(params),
			ft_maperror("plane : invalid parameters", g_data->prog_name));
	node->e_type = _plane;
	node->data = plane;
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	return (ft_free_strs(params), 0);
}

int	new_cylinder(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	t_cylinder	*cylinder;
	char		**params;

	cylinder = malloc(sizeof(t_cylinder));
	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!cylinder || !params)
	{
		free(cylinder);
		free(node);
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data);
	}
	if (check_args_count(params, 6, 6) == -1)
		return (free(cylinder), ft_free_strs(params),
			ft_maperror("cylinder : invalid parameters", g_data->prog_name));
	if (parse_pos(params[1], &cylinder->pos, 0) || parse_pos(params[2],
			&cylinder->rot, 1) || parse_float(params[3], &cylinder->diameter)
		|| parse_float(params[4], &cylinder->height)
		|| parse_raw_color(params[5], &cylinder->color))
		return (free(cylinder), ft_free_strs(params),
			ft_maperror("cylinder : invalid parameters", g_data->prog_name));
	node->e_type = _cylinder;
	node->data = cylinder;
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
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
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data);
	if (!ft_strncmp(obj_line, "sp", 1) && ft_isspace(obj_line[2]))
	{
		ret = new_sphere(p_data, obj_line, g_data, node);
		p_data->obj_count++;
	}
	else if (!ft_strncmp(obj_line, "pl", 1) && ft_isspace(obj_line[2]))
	{
		ret = new_plane(p_data, obj_line, g_data, node);
		p_data->obj_count++;
	}
	else if (!ft_strncmp(obj_line, "cy", 1) && ft_isspace(obj_line[2]))
	{
		ret = new_cylinder(p_data, obj_line, g_data, node);
		p_data->obj_count++;
	}
	if (ret)
		(free(obj_line), free(node), clean_exit(1, g_data, p_data));
}
