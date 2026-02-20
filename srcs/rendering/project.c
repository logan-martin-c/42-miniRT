/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:14:39 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/18 11:47:04 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_vect3	apply_perspective(t_vect3 *xyz, t_vect3 *xy, double factor)
// {
// 	xyz->z = -xyz->z;
// 	xy->x = (WIN_WIDTH / 2.0f + xyz->x * factor / xyz->z);
// 	xy->y = (WIN_HEIGHT / 2.0f - xyz->y * factor / xyz->z);
// 	xy->z = xyz->z;
// 	return (*xy);
// }

// t_vect3	project(t_vect3 pos, t_cam_data *cam_data)
// {
// 	t_vect3	new_pos;
// 	float		yy;
// 	float		xx;

// 	pos.x -= cam_data->pos.x;
// 	pos.y -= cam_data->pos.y;
// 	pos.z -= cam_data->pos.z;
// 	xx = pos.x;
// 	pos.x = xx * cam_data->cos_yaw - pos.z * cam_data->sin_yaw;
// 	pos.z = xx * cam_data->sin_yaw + pos.z * cam_data->cos_yaw;
// 	yy = -pos.y;
// 	pos.y = yy * cam_data->cos_pitch + pos.z * cam_data->sin_pitch;
// 	pos.z = -yy * cam_data->sin_pitch + pos.z * cam_data->cos_pitch;
// 	new_pos.z = pos.z;
// 	return (apply_perspective(&pos, &new_pos, -539));
// }
