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

#ifndef VECTORS_MATHS_2_H
# define VECTORS_MATHS_2_H

static inline double	vector_mag(t_pos_xyz a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

static inline t_pos_xyz	vector_norm(t_pos_xyz a)
{
	double	mag;

	mag = vector_mag(a);
	a.x = a.x / mag;
	a.y = a.y / mag;
	a.z = a.z / mag;
	return (a);
}

static inline t_pos_xyz	vector_cross(t_pos_xyz a, t_pos_xyz b)
{
	t_pos_xyz	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

static inline t_pos_xyz	vector_max_mag(t_pos_xyz a, float max_mag)
{
	int	mag;

	mag = vector_mag(a);
	if (mag > max_mag)
		a = vector_mult(vector_norm(a), max_mag);
	return (a);
}

#endif
