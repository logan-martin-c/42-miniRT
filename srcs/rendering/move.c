/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:27:34 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/15 22:44:24 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sin_cos_cam(t_cam_data *cam)
{
	double	yaw;
	double	pitch;

	yaw = cam->angle.y / NORM_PREC;
	pitch = cam->angle.x / NORM_PREC;
	cam->cos_yaw = cos(yaw);
	cam->sin_yaw = sin(yaw);
	cam->cos_pitch = cos(pitch);
	cam->sin_pitch = sin(pitch);
}

int	rotate_cam(t_cam_data *cam, t_mlx_data *mlx)
{
	int			x;
	int			y;
	static int	l_x = -1;
	static int	l_y = -1;

	mlx_mouse_get_pos(mlx->mlx, mlx->win, &x, &y);
	x -= WIN_WIDTH / 2;
	y -= WIN_HEIGHT / 2;
	if (l_x == -1)
		l_x = x;
	if (l_y == -1)
		l_y = y;
	// if (x > 300 || y > 300 || x < -300 || y < -300)
	// {
	// 	l_x -= x;
	// 	l_y -= y;
	// 	x = 0;
	// 	y = 0;
	// 	mlx_mouse_move(mlx->mlx, mlx->win, WIN_WIDTH / 2,
	//		WIN_HEIGHT / 2);
	// }
	cam->angle.y += (x * NORM_PREC - l_x * NORM_PREC) * 0.01;
	if ((cam->angle.x > -1.570796 * NORM_PREC || y * NORM_PREC - l_y * NORM_PREC > 0)
		&& (cam->angle.x < 1.570796 * NORM_PREC || y * NORM_PREC - l_y * NORM_PREC < 0))
		cam->angle.x += (y * NORM_PREC - l_y * NORM_PREC) * 0.01;
	l_x = x;
	l_y = y;
	// printf("cam pitch :%ld\n", cam->angle.x);
	// printf("cam yaw :%ld\n", cam->angle.y);
	// printf("cam roll :%ld\n", cam->angle.z);
	return (sin_cos_cam(cam), 1);
}

void	update_cam_pos(t_cam_data *cam, int elapsed)
{
	long	xx;
	long	yy;
	long	zz;

	xx = cam->move.x * 1e3;
	yy = cam->move.y * 1e3;
	zz = cam->move.z * 1e3;
	cam->move.x = xx * cam->cos_yaw + zz * cam->sin_yaw;
	cam->move.y = yy;
	cam->move.z = - xx * cam->sin_yaw + zz * cam->cos_yaw;
	// xx = cam->move.x * 1e3;
	// zz = cam->move.z * 1e3;
	cam->pos.x += ((double)cam->move.x * (double)elapsed / 10000000 * cam->speed) * 1e3;
	cam->pos.y += ((double)cam->move.y * (double)elapsed / 10000000 * cam->speed) * 1e3;
	cam->pos.z += ((double)cam->move.z * (double)elapsed / 10000000 * cam->speed) * 1e3;
	//printf("cam x :%f\n", ((double)cam->move.z * (double)elapsed / 1000000 * cam->speed) * 1e3);
	// printf("cam x :%ld\n", cam->pos.x);
	// printf("cam y :%ld\n", cam->pos.y);
	// printf("cam z :%ld\n", cam->pos.z);
}
