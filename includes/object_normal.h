/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_normal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:14:22 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 11:57:21 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_NORMAL_H
# define OBJECT_NORMAL_H

# include "minirt.h"
# include "vectors_maths_1.h"
# include "vectors_maths_2.h"

static inline t_vect3	sphere_normal(t_object *object, t_vect3 point,
		t_vect3 ray_dir, bool *direction)
{
	t_vect3	normal;

	normal.x = point.x - object->pos.x;
	normal.y = point.y - object->pos.y;
	normal.z = point.z - object->pos.z;
	normal = vector_norm(normal);
	if (dot_product(normal, ray_dir) < 0)
		return (*direction = false, normal);
	return (*direction = true, vectors_sub((t_vect3){0, 0, 0}, normal));
}

#endif