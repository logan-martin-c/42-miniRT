/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:27:34 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/06 14:34:57 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "moving.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include "vectors_rotations.h"

void	rotate_cam(t_cam_data *cam, t_mlx_data *mlx, bool *rotating,
		t_object *obj)
{
	t_vect2			mouse_p;
	static t_vect2	last_mouse_p = {-1, -1};

	mlx_mouse_get_pos(mlx->mlx, mlx->win, &mouse_p.x, &mouse_p.y);
	if (init_pos(&mouse_p, &last_mouse_p))
		return ;
	center_mouse(&mouse_p, &last_mouse_p, mlx);
	*rotating = true;
	if (!obj)
	{
		cam->forward = vector_rot(cam->forward, (float)(mouse_p.y
					- last_mouse_p.y) / 1e3, (float)(mouse_p.x
					- last_mouse_p.x) / 1e3, 0);
		cam->right = vector_norm(vector_cross((t_vect3){0, 1, 0},
					cam->forward));
		cam->up = vector_norm(vector_cross(cam->forward, cam->right));
	}
	else
		rotate_object(obj, (t_vect2){mouse_p.x - last_mouse_p.x, mouse_p.y
			- last_mouse_p.y});
	last_mouse_p.x = mouse_p.x;
	last_mouse_p.y = mouse_p.y;
}

t_vect3	get_final_moving_vector(t_vect3 mv, t_vect3 lasting, t_cam_data *cam,
		int elapsed)
{
	t_vect3	moving_vector;
	float	factor;

	moving_vector = lasting;
	factor = ((float)elapsed / 1000000.0) * (float)cam->speed * 5;
	if (mv.x)
		moving_vector = vectors_add(moving_vector, vector_mult(cam->right, mv.x
					* factor));
	if (mv.y)
		moving_vector = vectors_add(moving_vector, vector_mult((t_vect3){0, 1,
					0}, mv.y * factor));
	if (mv.z)
		moving_vector = vectors_add(moving_vector, vector_mult(cam->forward,
					mv.z * factor));
	return (vector_max_mag(moving_vector, cam->speed));
}

void	update_cam_pos(t_interface *input, t_cam_data *cam, int elapsed,
		bool *moving)
{
	t_vect3	mv;
	t_vect3	lasting;
	float	lasting_mag;
	t_vect3	moving_vector;

	mv = (t_vect3){input->d - input->a, input->space - input->ctrl, input->w
		- input->s};
	lasting = get_lasting();
	lasting_mag = vector_mag(lasting);
	if (!mv.x && !mv.y && !mv.z && !lasting_mag)
		return ;
	*moving = true;
	moving_vector = get_final_moving_vector(mv, lasting, cam, elapsed);
	if (!mv.x && !mv.y && !mv.z && lasting_mag)
	{
		cam->pos = vectors_add(cam->pos, vector_mult(moving_vector, elapsed
					/ 1000000.0));
		set_moving_vector(0, moving_vector, elapsed);
	}
	else
	{
		cam->pos = vectors_add(cam->pos, vector_mult(moving_vector, elapsed
					/ 1000000.0));
		set_moving_vector(1, moving_vector, elapsed);
	}
}

void	move_cam(t_world_data *world, t_mlx_data *mlx, t_interface *key,
		int elapsed)
{
	world->moving = false;
	world->rotating = false;
	rotate_cam(&world->cam, mlx, &world->rotating, world->selected_obj);
	if (!world->selected_obj)
		update_cam_pos(key, &world->cam, elapsed, &world->moving);
	if (!world->moving && !world->rotating)
	{
		if (world->static_frames < 10000)
			world->static_frames++;
		else
			world->static_frames = -2;
	}
	else
		world->static_frames = -1;
}
