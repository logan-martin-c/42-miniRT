/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_cone.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:02:15 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 15:35:16 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UV_CONE_H
# define UV_CONE_H

# include "minirt.h"
# include "vectors_maths_1.h"
# include "vectors_maths_2.h"
# include "vectors_maths_4.h"
# include "uv_cylinder.h"
# define _USE_MATH_DEFINES

typedef struct s_co_uv
{
	t_vect3			v;
	float			h_proj;
	t_vect3			radial;
	t_vect3			helper;
	t_vect3			tangent;
	float			angle;
}					t_co_uv;

static inline t_uv	get_cone_uv(t_nearest_object hit)
{
	t_uv	uv;
	t_co_uv	co_uv;

	if (hit.e_hit_type == _caps)
		return (get_cylinder_cap_uv(hit));
	co_uv.v = vectors_sub(hit.collision_point, hit.obj->pos);
	co_uv.h_proj = dot_product(co_uv.v, hit.obj->rot);
	uv.v = co_uv.h_proj / hit.obj->u_data.cone.height;
	co_uv.radial = vector_norm(vectors_sub(co_uv.v, vector_mult(hit.obj->rot,
					co_uv.h_proj)));
	if (ft_abs_float(hit.obj->rot.y) > 0.999f)
		co_uv.helper = (t_vect3){1, 0, 0};
	else
		co_uv.helper = (t_vect3){0, 1, 0};
	co_uv.tangent = vector_norm(vector_cross(co_uv.helper, hit.obj->rot));
	co_uv.angle = atan2(dot_product(co_uv.radial, vector_cross(hit.obj->rot,
					co_uv.tangent)), dot_product(co_uv.radial, co_uv.tangent));
	uv.u = (co_uv.angle + M_PI) / (2.0f * M_PI);
	return (uv);
}

#endif
