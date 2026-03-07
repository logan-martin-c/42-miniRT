/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:49:24 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/07 17:07:53 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include "vectors_maths_4.h"
#define _USE_MATH_DEFINES
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

t_uv get_plane_uv(t_nearest_object hit);

t_uv get_cylinder_cap_uv(t_nearest_object hit)
{
    t_uv uv;
    t_vect3 p = hit.collision_point;
    t_vect3 center = hit.obj->pos;
    t_vect3 axis = hit.obj->rot;
    float radius = hit.obj->u_data.cylinder.diameter / 2.0f;
    t_vect3 v = vectors_sub(p, center);
    t_vect3 right = (ft_abs_float(axis.y) > 0.999f) ? (t_vect3){1, 0, 0} : (t_vect3){0, 1, 0};
    t_vect3 u_axis = vector_norm(cross_product(right, axis));
    t_vect3 v_axis = vector_norm(cross_product(axis, u_axis));
    float u_coord = dot_product(v, u_axis);
    float v_coord = dot_product(v, v_axis);
    uv.u = (u_coord / (2.0f * radius)) + 0.5f;
    uv.v = (v_coord / (2.0f * radius)) + 0.5f;

    return (uv);
}

t_uv get_cylinder_tube_uv(t_nearest_object hit)
{
    t_uv uv;
    t_vect3 v = vectors_sub(hit.collision_point, hit.obj->pos);
    t_vect3 axis = hit.obj->rot;
    
    float h_proj = dot_product(v, axis);
    uv.v = (h_proj + (hit.obj->u_data.cylinder.height / 2.0f)) / hit.obj->u_data.cylinder.height;
    t_vect3 radial = vector_norm(vectors_sub(v, vector_mult(axis, h_proj)));
    t_vect3 helper = (ft_abs_float(axis.y) > 0.999f) ? (t_vect3){1, 0, 0} : (t_vect3){0, 1, 0};
    t_vect3 tangent = vector_norm(cross_product(helper, axis));
    t_vect3 bitangent = cross_product(axis, tangent);

    float angle = atan2(dot_product(radial, bitangent), dot_product(radial, tangent));
    uv.u = (angle + M_PI) / (2.0f * M_PI);

    return (uv);
}

t_uv get_cone_uv(t_nearest_object hit)
{
    if (hit.hit_type == _caps)
        return (get_cylinder_cap_uv(hit));
    t_uv uv;
    t_vect3 v = vectors_sub(hit.collision_point, hit.obj->pos);
    float h_proj = dot_product(v, hit.obj->rot);
    uv.v = h_proj / hit.obj->u_data.cone.height;
    t_vect3 radial = vector_norm(vectors_sub(v, vector_mult(hit.obj->rot, h_proj)));
    t_vect3 helper = (fabs(hit.obj->rot.y) > 0.999f) ? (t_vect3){1, 0, 0} : (t_vect3){0, 1, 0};
    t_vect3 tangent = vector_norm(cross_product(helper, hit.obj->rot));
    float angle = atan2(dot_product(radial, cross_product(hit.obj->rot, tangent)), 
                        dot_product(radial, tangent));
    uv.u = (angle + M_PI) / (2.0f * M_PI);
    
    return (uv);
}

t_uv	get_sphere_uv(t_nearest_object hit)
{
	t_vect3	d;
	t_uv	uv;

	d = vector_norm(vectors_sub(hit.collision_point, hit.obj->pos));
	uv.u = 0.5 + (atan2(d.z, d.x) / (2 * M_PI));
	uv.v = 0.5 - (asin(d.y) / M_PI);
	return (uv);
}

t_uv	get_uv_coords(t_nearest_object hit)
{
	if (hit.obj->e_type == _sphere)
		return (get_sphere_uv(hit));
	if (hit.obj->e_type == _cylinder)
    {
        if (hit.hit_type == _caps)
            return (get_cylinder_cap_uv(hit));
        return (get_cylinder_tube_uv(hit));
    }
	if (hit.obj->e_type == _cone)
		return (get_cone_uv(hit));
	if (hit.obj->e_type == _plane)
		return (get_plane_uv(hit));
	return ((t_uv){0, 0});
}
