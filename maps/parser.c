/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:48:12 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 15:56:50 by lomartin         ###   ########.fr       */
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

int	set_cam(t_parsing_data *p_data, char *obj_line, t_global_data *g_data)
{
	char	**params;

	if (p_data->map_data.cam)
		return (ft_maperror("Multiple cam definition is forbidden",
				g_data->prog_name));
	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!params)
		return (ft_perror(NULL, g_data->prog_name));
	if (check_args_count(params, 4, 4) == -1)
		return (ft_free_strs(params), ft_maperror("camera : invalid parameters",
				g_data->prog_name));
	if (parse_pos(params[1], &g_data->world.cam.pos, 0) || parse_pos(params[2],
			&g_data->world.cam.angle, 1) || !ft_isdigit_str(params[3]))
		return (ft_free_strs(params), ft_maperror("camera : invalid parameters",
				g_data->prog_name));
	g_data->world.cam.fov = ft_atoi(params[3]);
	if (g_data->world.cam.fov > 180 || g_data->world.cam.fov < 0)
		return (ft_free_strs(params), ft_maperror("camera : invalid parameters",
				g_data->prog_name));
	p_data->map_data.cam = 1;
	return (ft_free_strs(params), 0);
}

int	set_light(t_parsing_data *p_data, char *obj_line, t_global_data *g_data)
{
	char	**params;
	float	raw_ratio;

	if (p_data->map_data.light)
		return (ft_maperror("Multiple light definition is forbidden",
				g_data->prog_name));
	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!params)
		return (ft_perror(NULL, g_data->prog_name));
	if (check_args_count(params, 4, 4) == -1)
		return (ft_free_strs(params), ft_maperror("light : invalid parameters",
				g_data->prog_name));
	if (parse_pos(params[1], &g_data->world.light.pos, 0)
		|| !ft_isfloat_str(params[2]) || parse_raw_color(params[3],
			&g_data->world.light.color))
		return (ft_free_strs(params), ft_maperror("light : invalid parameters",
				g_data->prog_name));
	raw_ratio = ft_atof(params[2]);
	if (raw_ratio > 1 || raw_ratio < 0)
		return (ft_free_strs(params), ft_maperror("light : invalid ratio",
				g_data->prog_name));
	g_data->world.light.ratio = 255 * raw_ratio;
	p_data->map_data.light = 1;
	return (ft_free_strs(params), 0);
}

int	set_ambient_light(t_parsing_data *p_data, char *obj_line,
		t_global_data *g_data)
{
	char	**params;
	float	raw_ratio;

	if (p_data->map_data.ambient_light)
		return (ft_maperror("Multiple ambient light definition is forbidden",
				g_data->prog_name));
	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!params)
		return (ft_perror(NULL, g_data->prog_name));
	if (check_args_count(params, 3, 3) == -1)
		return (ft_free_strs(params),
			ft_maperror("ambient light : invalid parameters",
				g_data->prog_name));
	if (!ft_isfloat_str(params[1]) || parse_raw_color(params[2],
			&g_data->world.ambient_light.color))
		return (ft_free_strs(params),
			ft_maperror("ambient light : invalid parameters",
				g_data->prog_name));
	raw_ratio = ft_atof(params[1]);
	if (raw_ratio > 1 || raw_ratio < 0)
		return (ft_free_strs(params),
			ft_maperror("ambient light : invalid ratio", g_data->prog_name));
	g_data->world.ambient_light.ratio = 255 * raw_ratio;
	p_data->map_data.ambient_light = 1;
	return (ft_free_strs(params), 0);
}

void	parse_object(t_parsing_data *p_data, char *obj_line,
		t_global_data *g_data)
{
	int			ret;
	t_object	*node;

	ret = 0;
	node = malloc(sizeof(t_object));
	if (!node)
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data);
	if (!ft_strncmp(obj_line, "C", 1) && ft_isspace(obj_line[1]))
		ret = set_cam(p_data, obj_line, g_data);
	else if (!ft_strncmp(obj_line, "L", 1) && ft_isspace(obj_line[1]))
		ret = set_light(p_data, obj_line, g_data);
	else if (!ft_strncmp(obj_line, "A", 1) && ft_isspace(obj_line[1]))
		ret = set_ambient_light(p_data, obj_line, g_data);
	else if (!ft_strncmp(obj_line, "sp", 1) && ft_isspace(obj_line[2]))
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
	else
	{
		ft_maperror("Invalid object type", g_data->prog_name);
		(free(obj_line), free(node), clean_exit(1, g_data, p_data));
		exit(EXIT_FAILURE);
	}
	if (ret)
		(free(obj_line), free(node), clean_exit(1, g_data, p_data));
}

int	parse_map(int map_fd, t_global_data *g_data, t_parsing_data *p_data)
{
	char	*obj_line;

	obj_line = "";
	while (obj_line)
	{
		obj_line = get_next_line(map_fd);
		if (!obj_line)
			return (0);
		if (obj_line[ft_strlen(obj_line) - 1] == '\n')
			obj_line[ft_strlen(obj_line) - 1] = '\0';
		parse_object(p_data, obj_line, g_data);
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
