/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_plane.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 16:47:37 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 15:35:21 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UV_PLANE_H
# define UV_PLANE_H

# include "minirt.h"
# include "vectors_maths_1.h"
# include "vectors_maths_2.h"
# include "vectors_maths_4.h"
# define _USE_MATH_DEFINES

typedef struct s_pl_uv
{
	t_vect3	u_axis;
	t_vect3	v_axis;
	float	scale;
	t_vect3	helper;
	t_vect3	p;
}			t_pl_uv;

t_uv	get_plane_uv(t_nearest_object hit)
{
	t_uv	uv;
	t_pl_uv	pl_uv;

	pl_uv.scale = 40.0f;
	if (ft_abs_float(hit.normal.y) > 0.999f)
		pl_uv.helper = (t_vect3){1, 0, 0};
	else
		pl_uv.helper = (t_vect3){0, 1, 0};
	pl_uv.u_axis = vector_norm(vector_cross(pl_uv.helper, hit.normal));
	pl_uv.v_axis = vector_cross(hit.normal, pl_uv.u_axis);
	pl_uv.p = vectors_sub(hit.collision_point, hit.obj->pos);
	uv.u = dot_product(pl_uv.p, pl_uv.u_axis) / pl_uv.scale;
	uv.v = dot_product(pl_uv.p, pl_uv.v_axis) / pl_uv.scale;
	uv.u = uv.u - floor(uv.u);
	uv.v = uv.v - floor(uv.v);
	return (uv);
}

#endif