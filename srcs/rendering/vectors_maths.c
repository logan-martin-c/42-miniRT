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

#include "minirt.h"

t_pos_xyz	vectors_add(t_pos_xyz a, t_pos_xyz b)
{
	return ((t_pos_xyz){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_pos_xyz	vectors_sub(t_pos_xyz a, t_pos_xyz b)
{
	return ((t_pos_xyz){a.x - b.x, a.y - b.y, a.z - b.z});
}

double	vector_mag(t_pos_xyz a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

long	dot_product(t_pos_xyz a, t_pos_xyz b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_pos_xyz	vector_mult(t_pos_xyz a, int scal)
{
	a.x *= scal;
	a.y *= scal;
	a.z *= scal;
	return (a);
}

t_pos_xyz	vector_norm(t_pos_xyz a)
{
	double	mag;

	mag = vector_mag(a);
	a.x = a.x / mag;
	a.y = a.y / mag;
	a.z = a.z / mag;
	return (a);
}

t_pos_xyz	vector_cross(t_pos_xyz a, t_pos_xyz b)
{
	t_pos_xyz	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}
