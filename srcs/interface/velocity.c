/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   velocity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:33:06 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/20 10:00:36 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "vectors_maths_1.h"

t_vect3	velocity(int mode, t_vect3 moving_vector)
{
	static t_vect3	last_moving_vector;

	if (mode)
		last_moving_vector = moving_vector;
	return (last_moving_vector);
}

t_vect3	get_lasting(void)
{
	return (velocity(0, (t_vect3){0, 0, 0}));
}

void	set_moving_vector(bool moving, t_vect3 move, int elapsed)
{
	static float	veloc = 0;
	t_vect3			moving_vector;

	moving_vector = get_lasting();
	if (moving)
	{
		veloc = 1;
		moving_vector = move;
	}
	else if (!moving && veloc > 0)
	{
		veloc -= 0.1 * veloc * (float)elapsed * 1e-6;
		moving_vector = vector_mult(moving_vector, veloc);
	}
	velocity(1, moving_vector);
}
