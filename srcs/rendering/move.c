/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:27:34 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/20 09:59:55 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include "vectors_rotations.h"

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

void	rotate_cam(t_cam_data *cam, t_mlx_data *mlx, bool *rotating)
{
	int			x;
	int			y;
	static int	l_x = -1;
	static int	l_y = -1;

	mlx_mouse_get_pos(mlx->mlx, mlx->win, &x, &y);
	if (init_pos(&x, &y, &l_x, &l_y))
		return ;
	*rotating = true;
	// if (x > 300 || y > 300 || x < -300 || y < -300)
	// {
	// 	l_x -= x;
	// 	l_y -= y;
	// 	x = 0;
	// 	y = 0;
	// 	mlx_mouse_move(mlx->mlx, mlx->win, WIN_WIDTH / 2,
	//		WIN_HEIGHT / 2);
	// }
	cam->forward = vector_rot(cam->forward, (float)(y - l_y) * 1e-3, (float)(x
				- l_x) * 1e-3, 0);
	l_x = x;
	l_y = y;
	cam->right = vector_norm(vector_cross((t_vect3){0, 1, 0}, cam->forward));
	cam->up = vector_norm(vector_cross(cam->forward, cam->right));
}

void	update_cam_pos(t_interface *input, t_cam_data *cam, int elapsed,
		bool *moving)
{
	double	x;
	double	y;
	double	z;
	double	factor;
	t_vect3	lasting;
	float	lasting_mag;
	t_vect3	moving_vector;

	x = input->d - input->a;
	y = input->space - input->ctrl;
	z = input->w - input->s;
	lasting = get_lasting();
	lasting_mag = vector_mag(lasting);
	if (!x && !y && !z && !lasting_mag)
		return ;
	*moving = true;
	moving_vector = lasting;
	factor = ((float)elapsed / 1000000.0) * (float)cam->speed * 5;
	if (x)
		moving_vector = vectors_add(moving_vector, vector_mult(cam->right, x
			* factor));
	if (y)
		moving_vector = vectors_add(moving_vector, vector_mult((t_vect3){0, 1,
					0}, y * factor));
	if (z)
		moving_vector = vectors_add(moving_vector, vector_mult(cam->forward,
					z * factor));
	moving_vector = vector_max_mag(moving_vector, cam->speed);
	if (!x && !y && !z && lasting_mag)
	{
		cam->pos = vectors_add(cam->pos, vector_mult(moving_vector, elapsed / 1000000.0));
		set_moving_vector(0, moving_vector, elapsed);
	}
	else
	{
		cam->pos = vectors_add(cam->pos, vector_mult(moving_vector, elapsed / 1000000.0));
		set_moving_vector(1, moving_vector, elapsed);
	}
}

void	move_cam(t_world_data *world, t_mlx_data *mlx, t_interface *key,
		int elapsed)
{
	world->moving = false;
	world->rotating = false;
	rotate_cam(&world->cam, mlx, &world->rotating);
	update_cam_pos(key, &world->cam, elapsed, &world->moving);
	if (!world->moving && !world->rotating)
	{
		if (world->static_frames < 1000)
			world->static_frames++;
		else
			world->static_frames = 2000;
	}
	else
		world->static_frames = -1;
}
