/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_rotations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:20:04 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/17 14:48:47 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_ROTATIONS_H
# define VECTORS_ROTATIONS_H
# include "minirt.h"

t_pos_xyz	vector_rot(t_pos_xyz prev_pos, float pitch, float yaw, float roll)
{
	t_pos_xyz	new_pos;
	float		s;
	float		c;
	float		temp;

	s = sin(pitch);
	c = cos(pitch);
	new_pos.x = prev_pos.x;
	temp = prev_pos.y;
	new_pos.y = temp * c - prev_pos.z * s;
	new_pos.z = temp * s + prev_pos.z * c;
	s = sin(yaw);
	c = cos(yaw);
	temp = new_pos.x;
	new_pos.x = temp * c + new_pos.z * s;
	new_pos.z = - temp * s + new_pos.z * c;
	s = sin(roll);
	c = cos(roll);
	temp = new_pos.x;
	new_pos.x = temp* c - new_pos.y * s;
	new_pos.y =	temp * s + new_pos.y * c;
	return (new_pos);
}

#endif
