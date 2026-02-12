/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:48:12 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/12 15:03:07 by lomartin         ###   ########.fr       */
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
	if (!params[1] || !params[2] || !params[3] || params[4])
		return (free(sphere), free(node), ft_free_strs(params),
			ft_maperror("sphere : invalid parameters", g_data->prog_name));
	if (parse_pos(params[1], &sphere->pos) || parse_raw_color(params[3],
			&sphere->color))
		return (free(sphere), free(node), ft_free_strs(params),
			ft_maperror("sphere : invalid parameters", g_data->prog_name));
	sphere->diameter = ft_atof(params[2]);
	node->e_type = _sphere;
	node->data = sphere;
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	return (ft_free_strs(params), 0);
}

int	new_cam(t_parsing_data *p_data, char *obj_line, t_global_data *g_data,
		t_object *node)
{
	t_camera	*cam;
	char		**params;

	if (p_data->map_data.cam)
		return (ft_maperror("Multiple cam definition is forbidden",
				g_data->prog_name));
	cam = malloc(sizeof(t_camera));
	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!cam || !params)
	{
		(free(cam), free(node));
		clean_exit(ft_perror(NULL, g_data->prog_name), g_data, p_data);
	}
	if (!params[1] || !params[2] || !params[3] || params[4])
		return (free(cam), free(node), ft_free_strs(params),
			ft_maperror("camera : invalid parameters", g_data->prog_name));
	if (parse_pos(params[1], &cam->pos) || parse_pos(params[2], &cam->rot))
		return (free(cam), free(node), ft_free_strs(params),
			ft_maperror("camera : invalid parameters", g_data->prog_name));
	cam->fov = ft_atoi(params[2]);
	node->e_type = _camera;
	node->data = cam;
	ft_lstadd_front(&p_data->obj_lst, ft_lstnew(node));
	p_data->map_data.cam = 1;
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
		ret = new_cam(p_data, obj_line, g_data, node);
	else if (!ft_strncmp(obj_line, "sp", 1) && ft_isspace(obj_line[2]))
		ret = new_sphere(p_data, obj_line, g_data, node);
	else
	{
		ft_maperror("Invalid object type", g_data->prog_name);
		(free(obj_line), free(node), clean_exit(1, g_data, p_data));
		exit(EXIT_FAILURE);
	}
	if (ret)
		(free(obj_line), free(node), clean_exit(1, g_data, p_data));
	p_data->obj_count++;
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
		parse_object(p_data, obj_line, g_data);
		free(obj_line);
	}
	return (0);
}

void	lst_map_to_array(t_parsing_data *p_data, t_world_data *world)
{
	t_list	*next;
	int		i;

	world->objs = malloc(sizeof(t_object) * p_data->obj_count + 1);
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
