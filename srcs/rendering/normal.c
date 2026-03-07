/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:27:57 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/07 16:57:33 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include "vectors_maths_4.h"


t_vect3 get_normal_from_map(t_nearest_object hit)
{
    t_float_color color = get_texel_color(hit.obj->normal, hit.uv);
    t_vect3 map_n;

    map_n.x = (color.r * 2.0f) - 1.0f;
    map_n.y = (color.g * 2.0f) - 1.0f;
    map_n.z = (color.b * 2.0f) - 1.0f;
    return vector_norm(map_n);
}

/* 
t_vect3 calculate_sphere_tangent(t_vect3 normal)
{
    t_vect3 world_up = {0, 1, 0};

    if (ft_abs_float(normal.y) > 0.999f) 
        world_up = (t_vect3){0, 0, 1};
    
    return vector_norm(cross_product(world_up, normal));
} */

t_vect3 get_object_tangent(t_nearest_object hit)
{
    t_vect3 n = hit.normal;
    t_vect3 helper = (fabs(n.y) > 0.999f) ? (t_vect3){0, 0, 1} : (t_vect3){0, 1, 0};

    if (hit.obj->e_type == _plane || hit.hit_type == _caps)
        return vector_norm(cross_product(helper, n));
    if (hit.obj->e_type == _sphere)
        return vector_norm(cross_product(helper, n));
    if (hit.obj->e_type == _cylinder || hit.obj->e_type == _cone)
        return vector_norm(cross_product(hit.obj->rot, n));
    return vector_norm(cross_product(helper, n));
}

t_vect3 apply_normal_map(t_nearest_object hit)
{
    t_vect3 map_n = get_normal_from_map(hit);

    t_vect3 n = hit.normal;
    t_vect3 t = get_object_tangent(hit);
    t_vect3 b = cross_product(n, t);

    t_vect3 final_n;
    final_n.x = t.x * map_n.x + b.x * map_n.y + n.x * map_n.z;
    final_n.y = t.y * map_n.x + b.y * map_n.y + n.y * map_n.z;
    final_n.z = t.z * map_n.x + b.z * map_n.y + n.z * map_n.z;

    return vector_norm(final_n);
}
