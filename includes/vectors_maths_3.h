/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_maths_3.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 09:43:55 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/03 14:09:16 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_MATHS_3_H
# define VECTORS_MATHS_3_H

# include "minirt.h"

static inline float	fast_rand(void)
{
	static _Thread_local unsigned int xorshift_state = 42;
	xorshift_state ^= xorshift_state << 13;
	xorshift_state ^= xorshift_state >> 17;
	xorshift_state ^= xorshift_state << 5;
	return (xorshift_state * (1.0f / 4294967296.0f));
}

static inline t_vect3	get_random_vector(float min, float max)
{
	t_vect3	v;

	v.x = fast_rand() * (max - min) + min;
	v.y = fast_rand() * (max - min) + min;
	v.z = fast_rand() * (max - min) + min;
	vector_norm(v);
	return (v);
}

static inline t_vect3	get_diffuse_vector(t_vect3 normal, float reflectance)
{
	t_vect3	v;

	if (reflectance == 1)
		return (normal);
	while (1)
	{
		v = vectors_add(get_random_vector(-(1 - reflectance), (1
						- reflectance)), normal);
		if (dot_product(vector_norm(normal), vector_norm(v)) >= 0)
			return (v);
	}
	return (vectors_add(get_random_vector(-(1 - reflectance), (1
					- reflectance)), normal));
}

static inline t_vect3	reflect(t_vect3 v, t_vect3 n)
{
	return (vector_norm(vectors_sub(v, vector_mult(n, dot_product(v, n) * 2))));
}

static inline t_vect3	get_rand_p_light(t_vect3 light_pos, float radius)
{
	t_vect3	offset;

	offset.x = (fast_rand() * 2.0f - 1.0f) * radius;
	offset.y = (fast_rand() * 2.0f - 1.0f) * radius;
	offset.z = (fast_rand() * 2.0f - 1.0f) * radius;
	return (vectors_add(light_pos, offset));
}

#endif
