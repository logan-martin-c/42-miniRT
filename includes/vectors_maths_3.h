/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_maths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 09:43:55 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/16 11:11:51 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_MATHS_3_H
# define VECTORS_MATHS_3_H

# include "minirt.h"

static inline float fast_rand(void)
{
    static _Thread_local unsigned int  xorshift_state = 42;

    xorshift_state ^= xorshift_state << 13;
    xorshift_state ^= xorshift_state >> 17;
    xorshift_state ^= xorshift_state << 5;
    return (xorshift_state * (1.0f / 4294967296.0f));
}

static inline t_vect3 get_random_vector(float min, float max)
{
    t_vect3 v;

    v.x = fast_rand() * (max - min) + min;
    v.y = fast_rand() * (max - min) + min;
    v.z = fast_rand() * (max - min) + min;
    vector_norm(v);
    return (v);
}

static inline t_vect3  get_diffuse_vector(t_vect3 normal, float reflectance)
{
    t_vect3 v;

    if (reflectance == 1)
        return (normal);
    while (1)
    {
        v = get_random_vector(- (1 - reflectance), (1 - reflectance));
        if (v.x * v.y * v.z > 1.0f)
            continue ;
        v = vectors_add(v, normal);
        if (dot_product(vector_norm(normal), vector_norm(v)) >= 0)
            return (v);
        else
            return (vectors_sub((t_vect3){0, 0, 0}, v));
    }
}

static inline   t_vect3 refract(t_ray ray, t_vect3 n, float refraction)
{
    float cos_theta;
    t_vect3 r_out_perp;
    t_vect3 r_out_parralel;

    if (refraction == ray.origin_refraction)
        return (ray.dir);
    cos_theta = ft_min_float(dot_product(vectors_sub((t_vect3){0, 0, 0}, ray.dir), n), 1.0);
    r_out_perp = vector_mult(vectors_add(ray.dir, vector_mult(n, cos_theta)), ray.origin_refraction / refraction);
    r_out_parralel = vector_mult(n, - sqrt(ft_abs_float(1.0 - (vector_mag(r_out_perp) * vector_mag(r_out_perp)))));
    return (vectors_add(r_out_perp, r_out_parralel));
}

static inline t_vect3 reflect(t_vect3 v, t_vect3 n)
{
    // t_vect3 ret;
    //
    // ret = vector_norm(vectors_sub(v, vector_mult(n, dot_product(v, n) * 2)));
    // if (dot_product(v, ret) >= 0.9)
    //     return (n);
    // return (ret);
    return (vector_norm(vectors_sub(v, vector_mult(n, dot_product(v, n) * 2))));
}

static inline t_vect3   get_bounce(t_ray ray, t_vect3 n, int color, float refraction)
{
    t_color p_color;

    p_color = parse_color(color);
    if (p_color.alpha == 255)
        return (reflect(ray.dir, n));
    return (refract(ray, n, refraction));
}

#endif
