/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_maths_1.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 09:43:55 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/09 11:54:15 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_MATHS_1_H
# define VECTORS_MATHS_1_H

static inline t_vect3	vectors_add(t_vect3 a, t_vect3 b)
{
	return ((t_vect3){a.x + b.x, a.y + b.y, a.z + b.z});
}

static inline t_vect3	vectors_sub(t_vect3 a, t_vect3 b)
{
	return ((t_vect3){a.x - b.x, a.y - b.y, a.z - b.z});
}

static inline double	dot_product(t_vect3 a, t_vect3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static inline t_vect3	vectors_mult(t_vect3 a, t_vect3 b)
{
	t_vect3	new_vec3;

	new_vec3.x = a.x * b.x;
	new_vec3.y = a.y * b.y;
	new_vec3.z = a.z * b.z;
	return (new_vec3);
}

static inline t_vect3	vector_mult(t_vect3 a, float scal)
{
	a.x *= scal;
	a.y *= scal;
	a.z *= scal;
	return (a);
}

#endif