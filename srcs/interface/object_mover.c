/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_mover.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:48:04 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/04 13:49:47 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include "vectors_maths_3.h"
#include "vectors_rotations.h"
#include "moving.h"

static inline t_vect3	get_ray_dir(t_vect2 pos, t_viewport *viewport,
		t_cam_data *cam)
{
	double	u;
	double	v;
	float	rx;
	float	ry;

	rx = 0.5;
	ry = 0.5;
	u = (2.0 * (pos.x + rx) * INV_WIN_WIDTH - 1.0) * viewport->aspect_ratio
		* viewport->tan_theta;
	v = (1.0 - 2.0 * (pos.y + ry) * INV_WIN_HEIGHT) * viewport->tan_theta;
	return (vector_norm(vectors_add(cam->forward,
				vectors_add(vector_mult(cam->right, u), vector_mult(cam->up,
						v)))));
}

int	object_picker(int button, int x, int y, void *data)
{
	t_global_data		*g_data;
	t_ray				ray;
	t_nearest_object	nearest;

	g_data = data;
	if (button == 3)
	{
		g_data->world.selected_obj = NULL;
		return (0);
	}
	if (button != 1)
		return (-1);
	ray.dir = get_ray_dir((t_vect2){x, y}, &g_data->world.viewport,
			&g_data->world.cam);
	ray.origin = g_data->world.cam.pos;
	nearest = get_nearest_object(ray, &g_data->world);
	if (nearest.t == -1)
		g_data->world.selected_obj = NULL;
	else
		g_data->world.selected_obj = nearest.obj;
	return (0);
}

int	move_object(t_object *obj, t_world_data *world, t_interface *input,
		int elapsed)
{
	t_vect3	move;
	double	factor;
	t_vect3	moving_vector;

	if (!obj)
		return (-1);
	move.x = input->d - input->a;
	move.y = input->space - input->ctrl;
	move.z = input->w - input->s;
	if (!move.x && !move.y && !move.z)
		return (0);
	factor = ((double)elapsed / 1000000.0) * (double)world->cam.speed * 5.0;
	if (move.x)
		moving_vector = vectors_add(moving_vector, vector_mult(world->cam.right,
					move.x * factor));
	if (move.y)
		moving_vector = vectors_add(moving_vector, vector_mult((t_vect3){0, 1,
					0}, move.y * factor));
	if (move.z)
		moving_vector = vectors_add(moving_vector,
				vector_mult(world->cam.forward, move.z * factor));
	obj->pos = vectors_add(obj->pos, vector_mult(moving_vector, world->cam.speed
				* elapsed / 1000000.0));
	world->static_frames = -1;
	return (0);
}

void	rotate_object(t_object *obj, t_vect2 move)
{
	obj->rot = vector_rot(obj->rot, (float)(move.y) * 1e-3, (float)(move.x)
			* 1e-3, 0);
}
