/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:33:59 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/26 11:52:04 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_COLLISION_H
# define OBJECT_COLLISION_H

# include "minirt.h"
//
# include "vectors_maths_1.h"
# include "vectors_maths_2.h"
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
	if (t > 0)
		return (t);
	t = (-b + sqrt_delta) / 2.0;
	if (t > 0)
		return (t);
	return (-1.0);
}

static inline t_vect3 get_collision_point(t_ray ray, float t)
{
	t_vect3 point;

	point.x = ray.origin.x + t * ray.dir.x;
	point.y = ray.origin.y + t * ray.dir.y;
	point.z = ray.origin.z + t * ray.dir.z;
	return (point);
}

static inline float	check_object_collision(t_object *object, t_ray ray)
{
	if (object->e_type == _sphere)
		return (sphere_collision(ray, object));
	else if (object->e_type == _cylinder)
		return (-1);
	else if (object->e_type == _plane)
		return (-1);
	else if (object->e_type == _light)
		return (-1);
	return (-1);
}

#endif
