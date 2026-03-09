/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_maths_4.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:44:46 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 16:06:02 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_MATHS_4_H
# define VECTORS_MATHS_4_H

static inline t_vect3	get_rand_p_light(t_vect3 light_pos, float radius)
{
	t_vect3	offset;

	offset.x = (fast_rand() * 2.0f - 1.0f) * radius;
	offset.y = (fast_rand() * 2.0f - 1.0f) * radius;
	offset.z = (fast_rand() * 2.0f - 1.0f) * radius;
	return (vectors_add(light_pos, offset));
}

static inline bool	random_cond(float chances)
{
	if (fast_rand() < chances)
		return (true);
	return (false);
}

static inline float	get_reflectance(float cos_theta, float reflectance)
{
	return (1 / (reflectance + (1.0 - reflectance) * pow(1.0 - cos_theta,
				5.0)));
}

static inline t_vect3	get_bounce(t_ray *ray, t_vect3 n, t_material material,
		bool direction, t_world_data *world, t_vect3 collision_point)
{
	float	refraction;
	float	reflectance;

	if (direction)
		refraction = get_current_refraction(world->objs, world->obj_count,
				collision_point);
	else
		refraction = material.refraction;
	reflectance = material.color.a;
	if (reflectance)
		return (ray->e_blend_mode = _reflected, reflect(ray->dir, n));
	return (ray->e_blend_mode = _refracted, refract(ray, n, refraction));
}

#endif