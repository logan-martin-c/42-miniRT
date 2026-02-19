/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:33:59 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/18 15:31:59 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include <stdio.h>

double	sphere_collision(t_pos_xyz ray, t_object *object, t_pos_xyz cam_pos)
{
	t_pos_xyz	l;
	float		b;
	float		c;
	float		sqrt_delta;
	double		t;

	l = vectors_sub(cam_pos, object->pos);
	b = 2 * dot_product(ray, l);
	c = dot_product(l, l)
		- object->u_data.sphere.radius * object->u_data.sphere.radius;
	sqrt_delta = sqrt(b * b - 4 * 1.0 * c);
	t = (-b - sqrt_delta) / 2.0;
	if (t > 0)
		return (t);
	t = (-b + sqrt_delta) / 2.0;
	if (t > 0)
		return (t);
	return (-1.0);
}
