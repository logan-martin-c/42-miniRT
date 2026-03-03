/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:47:12 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/03 14:05:53 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "object_collision.h"

t_nearest_object	get_nearest_object(t_ray ray, t_world_data *world)
{
	int					i;
	int					nearest_i;
	float				t;
	float				new_t;
	t_nearest_object	nearest;

	t = -1;
	i = -1;
	nearest_i = -1;
	nearest.t = -1;
	nearest.u_data.obj = NULL;
	while (++i < world->obj_count)
	{
		new_t = check_object_collision(&world->objs[i], ray);
		if (new_t != -1 && (t == -1 || new_t < t))
		{
			nearest_i = i;
			t = new_t;
		}
	}
	if (nearest_i == -1)
		return (nearest);
	nearest.u_data.obj = world->objs + nearest_i;
	nearest.t = t;
	return (nearest);
}

t_nearest_object	get_nearest_light(t_ray ray, t_world_data *world)
{
	int					i;
	int					nearest_i;
	float				t;
	float				new_t;
	t_nearest_object	nearest;

	t = -1;
	i = -1;
	nearest_i = -1;
	nearest.t = -1;
	nearest.u_data.light = NULL;
	while (++i < world->light_count)
	{
		new_t = light_collision(ray, &world->lights[i]);
		if (new_t != -1 && (t == -1 || new_t < t))
		{
			nearest_i = i;
			t = new_t;
		}
	}
	if (nearest_i == -1)
		return (nearest);
	nearest.u_data.light = world->lights + nearest_i;
	nearest.t = t;
	return (nearest);
}

t_nearest_object	get_nearest_obj_or_light(t_ray ray, t_world_data *world)
{
	t_nearest_object	nearest_obj;
	t_nearest_object	nearest_light;

	nearest_obj.t = -1;
	nearest_light.t = -1;
	nearest_obj = get_nearest_object(ray, world);
	nearest_light = get_nearest_light(ray, world);
	if ((nearest_light.t < nearest_obj.t && nearest_light.t != -1)
		|| nearest_obj.t == -1)
		return (nearest_light.type = _obj_light, nearest_light);
	else
		return (nearest_light.type = _obj_object, nearest_obj);
}
