/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   velocity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:33:06 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/18 16:04:30 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "vectors_maths_1.h"

t_pos_xyz	velocity(int mode, t_pos_xyz moving_vector)
{
	static t_pos_xyz	last_moving_vector;

	if (mode)
		last_moving_vector = moving_vector;
	return (last_moving_vector);
}

t_pos_xyz	get_lasting(void)
{
	return (velocity(0, (t_pos_xyz){0, 0, 0}));
}

void	set_moving_vector(bool moving, t_pos_xyz move, int elapsed)
{
	static float	veloc = 0;
	t_pos_xyz		moving_vector;

	moving_vector = get_lasting();
	if (moving)
	{
		veloc = 1;
		moving_vector = move;
	}
	else if (!moving && veloc > 0)
	{
		veloc -= 2.0 * veloc * (float)elapsed * 1e-6;
		moving_vector = vector_mult(moving_vector, veloc);
	}
	velocity(1, moving_vector);
}
