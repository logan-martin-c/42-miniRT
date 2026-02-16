/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:14:39 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/15 22:44:39 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	my_mlx_pixel_put(t_mlx_data *mlx, t_pos_xyz pos, int color)
// {
// 	char		*dst;
// 	//int		index;
//
// 	if (pos.x < 0 || pos.x >= WIN_WIDTH || pos.y < 0 || pos.y >= WIN_HEIGHT)
// 		return ;
// 	// index = (int)pos.y * WIN_WIDTH + (int)pos.x;
// 	// if (!(index < 0 || index > WIN_HEIGHT
// 	// 		* WIN_WIDTH))
// 	// {
// 	// 	if (vars->z_buffer[index] > (int)pos.z)
// 	// 		return ;
// 	// 	vars->z_buffer[index] = (int)pos.z;
// 	// }
// 	dst = mlx->s_img_data.addr + ((int)pos.y * LINE_SIZE + (int)pos.x
// 			* BPP);
// 	*(unsigned int *)dst = color;
// }

t_pos_xyz	apply_perspective(t_pos_xyz *xyz, t_pos_xyz *xy, double factor)
{
	xyz->z = -xyz->z;
	xy->x = (WIN_WIDTH / 2.0f + xyz->x * factor / xyz->z);
	xy->y = (WIN_HEIGHT / 2.0f - xyz->y * factor / xyz->z);
	xy->z = xyz->z;
	return (*xy);
}

t_pos_xyz	project(t_pos_xyz pos, t_cam_data *cam_data)
{
	t_pos_xyz	new_pos;
	float		yy;
	float		xx;

	pos.x -= cam_data->pos.x;
	pos.y -= cam_data->pos.y;
	pos.z -= cam_data->pos.z;
	xx = pos.x;
	pos.x = xx * cam_data->cos_yaw - pos.z * cam_data->sin_yaw;
	pos.z = xx * cam_data->sin_yaw + pos.z * cam_data->cos_yaw;
	yy = -pos.y;
	pos.y = yy * cam_data->cos_pitch + pos.z * cam_data->sin_pitch;
	pos.z = - yy * cam_data->sin_pitch + pos.z * cam_data->cos_pitch;
	//new_pos.color = pos.color/*  + r_data->color */;d
	new_pos.z = pos.z;
	return (apply_perspective(&pos, &new_pos, -539));
}
