/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_objects_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:37:55 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/09 11:48:37 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "json.h"

int	json_sphere_params(t_pair *pair, t_object *obj, t_parsing_check *check,
		t_global_data *g_data)
{
	char	*error;
	int		ret;

	if (!ft_strcmp(pair->key, "position") && !check->pos)
		return (check->pos = 1, parse_json_pos(&pair->value, &obj->pos, false));
	if (!ft_strcmp(pair->key, "rotation") && !check->rot)
		return (check->rot = 1, parse_json_pos(&pair->value, &obj->rot, true));
	if (!ft_strcmp(pair->key, "diameter") && !check->diamet)
		return (check->diamet = 1, parse_json_float(&pair->value,
				&obj->u_data.sphere.radius, _positive));
	ret = parse_json_material(pair, check, &obj->material);
	if (ret && ret != 2)
		return (1);
	if (!ret)
		return (0);
	error = ft_strjoin_mult(3, "invalid sphere parameter '", pair->key, "'");
	ft_maperror(error, -1, g_data->prog_name);
	return (free(error), 1);
}

int	json_to_sphere(t_json json, t_global_data *g_data, t_world_data *world)
{
	size_t			i;
	t_parsing_check	check;

	ft_bzero(&check, sizeof(check));
	if (json.e_type != _brace)
		return (1);
	world->objs = ft_realloc(world->objs, world->obj_count * sizeof(t_object),
			(world->obj_count + 1) * sizeof(t_object));
	if (!world->objs)
		return (ft_perror(NULL, g_data->prog_name));
	set_default_obj(world->objs + world->obj_count);
	i = -1;
	while (++i < json.u_data.s_brace.size)
	{
		if (json_sphere_params(json.u_data.s_brace.data + i, world->objs
				+ world->obj_count, &check, g_data))
			return (1);
	}
	world->objs[world->obj_count].u_data.sphere.radius *= 0.5;
	world->objs[world->obj_count].e_type = _sphere;
	++world->obj_count;
	if (!check.pos || !check.color || !check.diamet)
		return (ft_maperror("incomplete sphere parameters", -1,
				g_data->prog_name));
	return (0);
}

int	json_cylinder_params(t_pair *pair, t_object *obj, t_parsing_check *check,
		t_global_data *g_data)
{
	int		ret;
	char	*error;

	if (!ft_strcmp(pair->key, "position") && !check->pos)
		return (check->pos = 1, parse_json_pos(&pair->value, &obj->pos, false));
	if (!ft_strcmp(pair->key, "rotation") && !check->rot)
		return (check->rot = 1, parse_json_pos(&pair->value, &obj->rot, true));
	if (!ft_strcmp(pair->key, "diameter") && !check->diamet)
		return (check->diamet = 1, parse_json_float(&pair->value,
				&obj->u_data.cylinder.radius, _positive));
	if (!ft_strcmp(pair->key, "height") && !check->height)
		return (check->height = 1, parse_json_float(&pair->value,
				&obj->u_data.cylinder.height, _positive));
	ret = parse_json_material(pair, check, &obj->material);
	if (ret && ret != 2)
		return (1);
	if (!ret)
		return (0);
	error = ft_strjoin_mult(3, "invalid cylinder parameter '", pair->key, "'");
	ft_maperror(error, -1, g_data->prog_name);
	return (free(error), 1);
}

int	json_to_cylinder(t_json json, t_global_data *g_data, t_world_data *world)
{
	size_t			i;
	t_parsing_check	check;

	if (json.e_type != _brace || (ft_bzero(&check, sizeof(check)), 0))
		return (1);
	world->objs = ft_realloc(world->objs, world->obj_count * sizeof(t_object),
			(world->obj_count + 1) * sizeof(t_object));
	if (!world->objs)
		return (ft_perror(NULL, g_data->prog_name));
	set_default_obj(world->objs + world->obj_count);
	i = -1;
	while (++i < json.u_data.s_brace.size)
	{
		if (json_cylinder_params(json.u_data.s_brace.data + i, world->objs
				+ world->obj_count, &check, g_data))
			return (1);
	}
	world->objs[world->obj_count].u_data.cylinder.radius *= 0.5;
	world->objs[world->obj_count].e_type = _cylinder;
	++world->obj_count;
	if (!check.pos || !check.rot || !check.color || !check.diamet
		|| !check.height)
		return (ft_maperror("incomplete cylinder parameters", -1,
				g_data->prog_name));
	return (0);
}
