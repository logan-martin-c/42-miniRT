/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_maths_4.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 11:44:46 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/09 14:11:14 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_MATHS_4_H
# define VECTORS_MATHS_4_H

# include "minirt.h"
# include "vectors_maths_1.h"
# include "vectors_maths_3.h"

static inline t_vect3	random_unit_vector(void)
{
	float	r;
	float	x;
	float	y;
	float	z;
	float	a;

	z = fast_rand() * 2.0f - 1.0f;
	a = fast_rand() * 2.0f * 3.14159265f;
	r = sqrt(1.0f - z * z);
	x = r * cos(a);
	y = r * sin(a);
	return ((t_vect3){x, y, z});
}

static inline t_vect3	cross_product(t_vect3 a, t_vect3 b)
{
	t_vect3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

#endif