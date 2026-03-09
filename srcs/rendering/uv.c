/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:49:24 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 15:26:17 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "uv_cylinder.h"
//
#include "uv_cone.h"
#include "uv_plane.h"
#include "uv_sphere.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include "vectors_maths_4.h"
#define _USE_MATH_DEFINES

t_uv	get_uv_coords(t_nearest_object hit)
{
	if (hit.obj->e_type == _sphere)
		return (get_sphere_uv(hit));
	if (hit.obj->e_type == _cylinder)
	{
		if (hit.e_hit_type == _caps)
			return (get_cylinder_cap_uv(hit));
		return (get_cylinder_tube_uv(hit));
	}
	if (hit.obj->e_type == _cone)
		return (get_cone_uv(hit));
	if (hit.obj->e_type == _plane)
		return (get_plane_uv(hit));
	return ((t_uv){0, 0});
}
