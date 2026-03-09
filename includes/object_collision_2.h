/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision_2.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:45:10 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 16:52:39 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_COLLISION_2_H
# define OBJECT_COLLISION_2_H

static inline t_nearest_object	new_sphere_collision(t_ray ray, t_object *obj)
{
	t_nearest_object	hit;
	t_vect3				l;
	float				b;
	float				c;
	float				delta;
	float				sqrt_delta;
	float				t;
	t_vect3				hit_point;
	t_vect3				normal_vec;

	hit.t = -1.0f;
	hit.obj = obj;
	hit.is_inside = false;
	l = vectors_sub(ray.origin, obj->pos);
	b = 2.0f * dot_product(ray.dir, l);
	c = dot_product(l, l) - (obj->u_data.sphere.radius
			* obj->u_data.sphere.radius);
	delta = b * b - 4.0f * c;
	if (delta < 0)
		return (hit.t = -1, hit);
	sqrt_delta = sqrt(delta);
	t = (-b - sqrt_delta) / 2.0f;
	if (t < 0.001f)
		t = (-b + sqrt_delta) / 2.0f;
	if (t < 0.001f)
		return (hit.t = -1, hit);
	hit.t = t;
	hit.obj = obj;
	hit_point = vectors_add(ray.origin, vector_mult(ray.dir, t));
	normal_vec = vectors_sub(hit_point, obj->pos);
	hit.normal = vector_mult(normal_vec, 1.0f / obj->u_data.sphere.radius);
	if (dot_product(hit.normal, ray.dir) > 0)
	{
		hit.is_inside = true;
		hit.normal = vector_mult(hit.normal, -1.0f);
	}
	return (hit);
}

static inline t_nearest_object	plane_collision(t_ray ray, t_object *obj)
{
	t_nearest_object	hit;
	float				dot_on_rd;
	float				t;
	t_vect3				oc;

	hit.t = -1.0f;
	hit.obj = obj;
	hit.is_inside = false;
	dot_on_rd = dot_product(obj->rot, ray.dir);
	if (ft_abs_float(dot_on_rd) < 0.00001f)
		return (hit);
	oc = vectors_sub(obj->pos, ray.origin);
	t = dot_product(oc, obj->rot) / dot_on_rd;
	if (t < 0.001f)
		return (hit);
	hit.t = t;
	if (dot_on_rd > 0)
		hit.normal = vector_mult(obj->rot, -1.0f);
	else
		hit.normal = obj->rot;
	return (hit);
}

#endif