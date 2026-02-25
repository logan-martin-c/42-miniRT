/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_maths_2.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 09:43:55 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/25 14:22:34 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_MATHS_2_H
# define VECTORS_MATHS_2_H

static inline double	vector_mag(t_vect3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

static inline t_vect3	vector_norm(t_vect3 a)
{
	double	mag;

	mag = vector_mag(a);
	a.x = a.x / mag;
	a.y = a.y / mag;
	a.z = a.z / mag;
	return (a);
}

static inline t_vect3	vector_cross(t_vect3 a, t_vect3 b)
{
	t_vect3	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

static inline t_vect3	vector_max_mag(t_vect3 a, float max_mag)
{
	int	mag;

	mag = vector_mag(a);
	if (mag > max_mag)
		a = vector_mult(vector_norm(a), max_mag);
	return (a);
}

static inline t_vect3 vector_reflect(t_vect3 i, t_vect3 n)
{
    // R = I - 2 * dot(I, N) * N
    double dot = dot_product(i, n);
    t_vect3 scaled_n = vector_mult(n, 2.0 * dot);
    return (vectors_sub(i, scaled_n));
}

#endif
