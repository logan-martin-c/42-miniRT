/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:27:34 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/18 12:03:10 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include "vectors_rotations.h"

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

static inline int	init_pos(int *x, int *y, int *l_x, int *l_y)
{
	*x -= WIN_WIDTH * 0.5;
	*y -= WIN_HEIGHT * 0.5;
	if (*l_x == -1 && *l_y == -1)
	{
		*l_x = *x;
		*l_y = *y;
	}
	else if (*l_y == *y && *l_x == *x)
		return (1);
	return (0);
}

void	rotate_cam(t_cam_data *cam, t_mlx_data *mlx)
{
	int			x;
	int			y;
	static int	l_x = -1;
	static int	l_y = -1;

	mlx_mouse_get_pos(mlx->mlx, mlx->win, &x, &y);
	if (init_pos(&x, &y, &l_x, &l_y))
		return ;
	// if (x > 300 || y > 300 || x < -300 || y < -300)
	// {
	// 	l_x -= x;
	// 	l_y -= y;
	// 	x = 0;
	// 	y = 0;
	// 	mlx_mouse_move(mlx->mlx, mlx->win, WIN_WIDTH / 2,
	//		WIN_HEIGHT / 2);
	// }
	cam->move = vector_rot(cam->move, (float)(y - l_y) * 1e-3, (float)(x - l_x
				) * 1e-3, 0);
	l_x = x;
	l_y = y;
	cam->right = vector_norm(vector_cross((t_pos_xyz){0, 1, 0}, cam->move));
	cam->up = vector_norm(vector_cross(cam->move, cam->right));
}

void	update_cam_pos(t_interface *input, t_cam_data *cam, int elapsed)
{
	double	x;
	double	y;
	double	z;
	double	factor;

	factor = elapsed / 1000000.0 * (float)cam->speed;
	x = input->d - input->a;
	y = input->space - input->ctrl;
	z = input->w - input->s;
	if (!x && !y && !z)
		return ;
	if (x)
		cam->pos = vectors_add(cam->pos, vector_mult(cam->right, x * factor));
	if (y)
		cam->pos = vectors_add(cam->pos, vector_mult((t_pos_xyz){0, 1, 0}, y
					* factor));
	if (z)
		cam->pos = vectors_add(cam->pos, vector_mult(cam->move, z * factor));
	// printf("z : %lf\n", cam->pos.z);
}
