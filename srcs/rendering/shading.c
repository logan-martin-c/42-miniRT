/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:24:58 by adastugu          #+#    #+#             */
/*   Updated: 2026/02/20 17:22:18 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "colors_maths.h"
#include "mlx_utils.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#define _USE_MATH_DEFINES

t_pos_xyz get_p_normal(t_object object, t_pos_xyz p)
{
	t_pos_xyz n;

	n.x = p.x - object.pos.x;
	n.y = p.y - object.pos.y;
	n.z = p.z - object.pos.z;
	return (n);
}

t_pos_xyz get_p_pos(t_pos_xyz ray, t_pos_xyz cam_pos, float t)
{
	t_pos_xyz p;

	p.x = cam_pos.x + t * ray.x;
	p.y = cam_pos.y + t * ray.y;
	p.z = cam_pos.z + t * ray.z;
	return (p);
}

/// @brief more structs needed.
int compute_lighting(t_pos_xyz p, t_pos_xyz n, t_world_data *world)
{
	float intensity;
	t_pos_xyz l;
	float dot_l;

	intensity =  0.1; // world->ambient_light.ratio;
	l = vectors_sub(world->light.pos, p);
	dot_l = dot_product(n, l);
	if (dot_l > 0)
		intensity += world->light.ratio * dot_l / (vector_mag(n) * vector_mag(l));
	return (intensity);
}

int apply_lighting(int o_color, int intensity)
{
	t_color obj_splt_colors;

	obj_splt_colors = parse_color(o_color);
	obj_splt_colors.red *= intensity;
	obj_splt_colors.green *= intensity;
	obj_splt_colors.blue *= intensity;
	return (get_color(obj_splt_colors));
}

/// @brief calc P space pos, calc P normal, calc direct light intensity, return adjusted color
int shading(t_pos_xyz ray, t_pos_xyz cam_pos, float t, t_object object, t_world_data *world)
{
	t_pos_xyz p;
	t_pos_xyz n;

	p = get_p_pos(ray, cam_pos, t);
	n = get_p_normal(object, p);
	//n = vector_norm(n);
	return (apply_lighting(object.color , compute_lighting(p, n, world)));
	
}
