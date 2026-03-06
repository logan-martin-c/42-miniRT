/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:33:59 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/06 18:30:29 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_COLLISION_H
# define OBJECT_COLLISION_H

# include "minirt.h"
//
# include "vectors_maths_1.h"
# include "vectors_maths_2.h"
# include "object_collision_2.h"
# include <stdio.h>

static inline double	sphere_collision(t_ray ray, t_object *object)
{
	t_vect3	l;
	float	b;
	float	c;
	float	sqrt_delta;
	double	t;

	l = vectors_sub(ray.origin, object->pos);
	b = 2 * dot_product(ray.dir, l);
	c = dot_product(l, l) - object->u_data.sphere.radius
		* object->u_data.sphere.radius;
	sqrt_delta = sqrt(b * b - 4 * 1.0 * c);
	t = (-b - sqrt_delta) / 2.0;
	if (t > 0.001)
		return (t);
	t = (-b + sqrt_delta) / 2.0;
	if (t > 0.001)
		return (t);
	return (-1.0);
}

static inline t_vect3	get_collision_point(t_ray ray, float t)
{
	t_vect3	point;

	point.x = ray.origin.x + t * ray.dir.x;
	point.y = ray.origin.y + t * ray.dir.y;
	point.z = ray.origin.z + t * ray.dir.z;
	return (point);
}

static inline t_nearest_object	check_object_collision(t_object *object, t_ray ray)
{
	t_nearest_object hit;
	
	if (object->e_type == _sphere)
		return (new_sphere_collision(ray, object));
	else if (object->e_type == _cylinder)
		return (cylinder_collision(ray, object));
	else if (object->e_type == _plane)
		return (plane_collision(ray,  object));
	else if (object->e_type == _light)
		return (hit.t = -1, hit);
	return (hit.t = -1, hit);
}

static inline double	light_collision(t_ray ray, t_object *light)
{
	t_vect3	l;
	float	b;
	float	c;
	float	sqrt_delta;
	double	t;

	l = vectors_sub(ray.origin, light->pos);
	b = 2 * dot_product(ray.dir, l);
	c = dot_product(l, l) - light->u_data.light.radius * light->u_data.light.radius;
	sqrt_delta = sqrt(b * b - 4 * 1.0 * c);
	t = (-b - sqrt_delta) / 2.0;
	if (t > 0.01)
		return (t);
	t = (-b + sqrt_delta) / 2.0;
	if (t > 0.01)
		return (t);
	return (-1.0);
}

#endif
