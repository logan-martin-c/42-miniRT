/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision_2.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:45:10 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/05 17:35:28 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"

static inline bool	cylinder_collision(t_ray ray, t_object *object, t_nearest_object *hit)
{
	t_vect3 ba = vectors_sub(object->pos, vector_mult(object->rot, object->u_data.cylinder.height / 2.0));
	t_vect3 oc = vectors_sub(ray.origin, object->pos);
	float radius = object->u_data.cylinder.diameter;
	float baba = dot_product(ba, ba);
	float bard = dot_product(ba, ray.dir) ;
	float baoc = dot_product(ba, oc);
	float k2 = baba - bard * bard;
	float k1 = baba*dot_product(oc, ray.dir) - baoc*bard;
	float k0 = baba*dot_product(oc,oc) - baoc*baoc - radius * radius * baba;
	float h = k1*k1 - k2 * k0;
	if (h < 0.0f)
		return false;
	h = sqrt(h);
	float t = (-k1 - h) / k2;
	float y  = baoc + t*bard;
	if (y > 0.0 && y < baba)
	{
		t_vect3 tmp = vectors_add(oc, vector_mult(ray.dir, t));
        t_vect3 projection = vector_mult(ba, y / baba);
        hit->normal = vector_norm(vectors_sub(tmp, projection));
		return (hit->t = t, true);
	}
	if (y < 0.0)
		t = 0.0;
	else
		t = baba;
	t = (t -baoc) / bard;
	if(ft_abs_float(k1+k2 *t) < h)
	{
		if (y < 0.0f)
			hit->normal = vector_mult(vector_norm(ba), -1.0f);
		else
			hit->normal = vector_mult(vector_norm(ba), 1.0f);
		return (hit->t = t, true);
	}
	return (false);
}
