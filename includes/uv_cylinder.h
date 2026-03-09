/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_cylinder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 13:58:42 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 14:13:16 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UV_CYLINDER_H
# define UV_CYLINDER_H

# include "minirt.h"
# include "vectors_maths_1.h"
# include "vectors_maths_2.h"
# include "vectors_maths_4.h"
# define _USE_MATH_DEFINES

typedef struct s_cy_uv
{
	t_vect3			p;
	t_vect3			center;
	t_vect3			axis;
	float			radius;
	t_vect3			v;
	t_vect3			right;
	t_vect3			u_axis;
	t_vect3			v_axis;
	float			u_coord;
	float			v_coord;
	float			h_proj;
	t_vect3			radial;
	t_vect3			helper;
	t_vect3			tangent;
	t_vect3			bitangent;
	float			angle;
}					t_cy_uv;

static inline t_uv	get_cylinder_cap_uv(t_nearest_object hit)
{
	t_cy_uv	cy_uv;
	t_uv	uv;

	cy_uv.p = hit.collision_point;
	cy_uv.center = hit.obj->pos;
	cy_uv.axis = hit.obj->rot;
	cy_uv.radius = hit.obj->u_data.cylinder.radius;
	cy_uv.v = vectors_sub(cy_uv.p, cy_uv.center);
	if (ft_abs_float(cy_uv.axis.y) > 0.999f)
		cy_uv.right = (t_vect3){1, 0, 0};
	else
		cy_uv.right = (t_vect3){0, 1, 0};
	cy_uv.u_axis = vector_norm(cross_product(cy_uv.right, cy_uv.axis));
	cy_uv.v_axis = vector_norm(cross_product(cy_uv.axis, cy_uv.u_axis));
	cy_uv.u_coord = dot_product(cy_uv.v, cy_uv.u_axis);
	cy_uv.v_coord = dot_product(cy_uv.v, cy_uv.v_axis);
	return (uv.u = (cy_uv.u_coord / (2.0f * cy_uv.radius)) + 0.5f,
		uv.v = (cy_uv.v_coord / (2.0f * cy_uv.radius)) + 0.5f, uv);
}

static inline t_uv	get_cylinder_tube_uv(t_nearest_object hit)
{
	t_uv	uv;
	t_cy_uv	cy_uv;

	cy_uv.v = vectors_sub(hit.collision_point, hit.obj->pos);
	cy_uv.axis = hit.obj->rot;
	cy_uv.h_proj = dot_product(cy_uv.v, cy_uv.axis);
	uv.v = (cy_uv.h_proj + (hit.obj->u_data.cylinder.height / 2.0f))
		/ hit.obj->u_data.cylinder.height;
	cy_uv.radial = vector_norm(vectors_sub(cy_uv.v, vector_mult(cy_uv.axis,
					cy_uv.h_proj)));
	if (ft_abs_float(cy_uv.axis.y) > 0.999f)
		cy_uv.helper = (t_vect3){1, 0, 0};
	else
		cy_uv.helper = (t_vect3){0, 1, 0};
	cy_uv.tangent = vector_norm(cross_product(cy_uv.helper, cy_uv.axis));
	cy_uv.bitangent = cross_product(cy_uv.axis, cy_uv.tangent);
	cy_uv.angle = atan2(dot_product(cy_uv.radial, cy_uv.bitangent),
			dot_product(cy_uv.radial, cy_uv.tangent));
	uv.u = (cy_uv.angle + M_PI) / (2.0f * M_PI);
	return (uv);
}

#endif