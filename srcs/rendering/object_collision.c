/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:33:59 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/18 11:50:23 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include <stdio.h>

double	sphere_collision(t_pos_xyz ray, t_sphere *sphere, t_pos_xyz cam_pos)
{
	t_pos_xyz	l;
	float		b;
	float		c;
	float		sqrt_delta;
	double		t;

	l = vectors_sub(cam_pos, sphere->pos);
	b = 2 * dot_product(ray, l);
	c = dot_product(l, l) - sphere->radius * sphere->radius;
	sqrt_delta = sqrt(b * b - 4 * 1.0 * c);
	t = (-b - sqrt_delta) / 2.0;
	if (t > 1)
		return (t);
	t = (-b + sqrt_delta) / 2.0;
	if (t > 1)
		return (t);
	return (-1.0);
}
