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

static inline t_pos_xyz	vectors_add(t_pos_xyz a, t_pos_xyz b)
{
	return ((t_pos_xyz){a.x + b.x, a.y + b.y, a.z + b.z});
}

static inline t_pos_xyz	vectors_sub(t_pos_xyz a, t_pos_xyz b)
{
	return ((t_pos_xyz){a.x - b.x, a.y - b.y, a.z - b.z});
}

static inline double	dot_product(t_pos_xyz a, t_pos_xyz b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static inline t_pos_xyz	vector_mult(t_pos_xyz a, double scal)
{
	a.x *= scal;
	a.y *= scal;
	a.z *= scal;
	return (a);
}

#endif