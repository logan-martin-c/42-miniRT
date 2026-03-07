/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 16:47:37 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/07 17:09:00 by adastugu         ###   ########.fr       */
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

t_uv get_plane_uv(t_nearest_object hit)
{
    t_uv    uv;
    t_vect3 u_axis;
    t_vect3 v_axis;
    float   scale = 40.0f;
    t_vect3 helper = (ft_abs_float(hit.normal.y) > 0.999f) ? (t_vect3){1, 0, 0} : (t_vect3){0, 1, 0};
    u_axis = vector_norm(cross_product(helper, hit.normal));
    v_axis = cross_product(hit.normal, u_axis);
    t_vect3 p = vectors_sub(hit.collision_point, hit.obj->pos);
    uv.u = dot_product(p, u_axis) / scale;
    uv.v = dot_product(p, v_axis) / scale;
    uv.u = uv.u - floor(uv.u);
    uv.v = uv.v - floor(uv.v);

    return (uv);
}
