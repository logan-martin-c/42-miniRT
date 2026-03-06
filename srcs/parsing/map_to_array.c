/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:45:52 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/26 14:47:17 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	lst_objs_to_array(t_object **objs, t_list *obj_lst, int obj_count)
{
	int	i;

	*objs = malloc(sizeof(t_object) * obj_count);
	if (!*objs)
		return (1);
	i = -1;
	while (++i < obj_count)
	{
		if (((t_object *)obj_lst->content)->e_type != _light)
			memcpy(&objs[0][i], (t_object *)obj_lst->content, sizeof(t_object));
		else
			i--;
		obj_lst = obj_lst->next;
	}
	return (0);
}

int	lst_lights_to_array(t_object **lights, t_list *obj_lst, int light_count)
{
	int	i;

	*lights = malloc(sizeof(t_object) * light_count);
	if (!*lights)
		return (1);
	i = -1;
	while (++i < light_count)
	{
		if (((t_object *)obj_lst->content)->e_type == _light)
			memcpy(lights[0] + i,
				(t_object *)obj_lst->content,
				sizeof(t_object));
		else
			i--;
		obj_lst = obj_lst->next;
	}
	return (0);
}

int	lst_map_to_array(t_parsing_data *p_data, t_world_data *world)
{
	if (lst_objs_to_array(&world->objs, p_data->obj_lst,
			p_data->obj_count - p_data->light_count))
		return (1);
	world->obj_count = p_data->obj_count - p_data->light_count;
	if (lst_lights_to_array(&world->lights, p_data->obj_lst,
			p_data->light_count))
		return (1);
	world->light_count = p_data->light_count;
	return (0);
}
