/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_maths_3.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 09:43:55 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 23:17:37 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_MATHS_3_H
# define VECTORS_MATHS_3_H

# include "minirt.h"
# include "refraction.h"

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
    float   dot;

    if (reflectance == 1)
        return (normal);
    while (1)
    {
        v = get_random_vector(- (1 - reflectance), 1 - reflectance);
        if (v.x * v.y * v.z > 1.0f)
            continue ;
        v = vectors_add(v, normal);
        dot = dot_product(vector_norm(normal), vector_norm(v));
        if (dot >= 0.5)
            return (v);
        else if (dot <= -0.5)
            return (vectors_sub((t_vect3){0, 0, 0}, v));
    }
}

static inline t_vect3	reflect(t_vect3 v, t_vect3 n)
{
	// t_vect3 ret;
	//
	// ret = vector_norm(vectors_sub(v, vector_mult(n, dot_product(v, n) * 2)));
	// if (dot_product(v, ret) >= 0.9)
	//     return (n);
	// return (ret);
	return (vector_norm(vectors_sub(v, vector_mult(n, dot_product(v, n) * 2))));
}

static inline t_vect3	refract(t_ray *ray, t_vect3 n, float refraction)
{
	t_vect3	r_out_perp;
	t_vect3	r_out_parralel;
	float	cos_theta;

	if (refraction == ray->origin_refraction)
		return (ray->dir);
	cos_theta = -dot_product(ray->dir, n);
	// if (refraction * sqrt(1.0 - cos_theta * cos_theta) > 1.0)
	// 	return (ray->blend_mode = _reflected, reflect(ray->dir, n));
	r_out_perp = vector_mult(vectors_add(ray->dir, vector_mult(n, cos_theta)),
			ray->origin_refraction / refraction);
	r_out_parralel = vector_mult(n, -sqrt(ft_abs_float(1.0
					- (vector_mag(r_out_perp) * vector_mag(r_out_perp)))));
	return (vectors_add(r_out_perp, r_out_parralel));
}

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
	{
		refraction = get_current_refraction(world->objs, world->obj_count, collision_point);
		//reflectance = 0;
	}
	else
	{
		refraction = material.refraction;
	}
    reflectance = material.color.a;
	if (random_cond(/*get_reflectance(dot_product(vector_norm(ray->dir), vector_norm(n)), */reflectance))/*)*/
		return (ray->blend_mode = _reflected, reflect(ray->dir, n));
	return (ray->blend_mode = _refracted, refract(ray, n, refraction));
}

#endif
