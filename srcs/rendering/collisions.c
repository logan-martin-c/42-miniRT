/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:47:12 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/26 11:57:37 by lomartin         ###   ########.fr       */
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
	nearest.obj = NULL;
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
	nearest.obj = world->objs + nearest_i;
	nearest.t = t;
	return (nearest);
}
