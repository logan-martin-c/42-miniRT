/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_maths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 09:43:55 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/16 11:11:51 by lomartin         ###   ########.fr       */
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

static inline t_vect3	vector_mult(t_vect3 a, double scal)
{
	a.x *= scal;
	a.y *= scal;
	a.z *= scal;
	return (a);
}

#endif