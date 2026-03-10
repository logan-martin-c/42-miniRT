/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_sphere.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:37:25 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 15:35:23 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UV_SPHERE_H
# define UV_SPHERE_H

# include "minirt.h"
# include "vectors_maths_1.h"
# include "vectors_maths_2.h"
# include "vectors_maths_4.h"
# define _USE_MATH_DEFINES

typedef struct s_sp_uv
{
	t_vect3			d;
	t_vect3			local_up;
	t_vect3			helper;
	t_vect3			local_right;
	t_vect3			local_forward;
	float			x;
	float			y;
	float			z;
}					t_sp_uv;

static inline t_uv	get_sphere_uv(t_nearest_object hit)
{
	t_uv	uv;
	t_sp_uv	sp_uv;

	sp_uv.d = vector_norm(vectors_sub(hit.collision_point, hit.obj->pos));
	sp_uv.local_up = hit.obj->rot;
	if (ft_abs_float(sp_uv.local_up.y) > 0.999f)
		sp_uv.helper = (t_vect3){1, 0, 0};
	else
		sp_uv.helper = (t_vect3){0, 1, 0};
	sp_uv.local_right = vector_norm(vector_cross(sp_uv.helper,
				sp_uv.local_up));
	sp_uv.local_forward = vector_cross(sp_uv.local_up, sp_uv.local_right);
	sp_uv.x = dot_product(sp_uv.d, sp_uv.local_right);
	sp_uv.y = dot_product(sp_uv.d, sp_uv.local_up);
	sp_uv.z = dot_product(sp_uv.d, sp_uv.local_forward);
	uv.u = 0.5f + (atan2(sp_uv.z, sp_uv.x) / (2.0f * M_PI));
	uv.v = 0.5f - (asin(sp_uv.y) / M_PI);
	return (uv);
}

#endif
