/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:36:21 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/24 14:01:41 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "colors_maths.h"
#include "mlx_utils.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include "object_collision.h"
#define _USE_MATH_DEFINES

void	init_viewport(t_viewport *viewport, int fov)
{
	viewport->aspect_ratio = (double)WIN_WIDTH * (double)INV_WIN_HEIGHT;
	viewport->theta = fov * M_PI / 180.0;
	viewport->tan_theta = tan(viewport->theta * 0.5);
	viewport->ratio_tan_theta = viewport->aspect_ratio * viewport->tan_theta;
	viewport->vp_h = 2 * tan(viewport->theta * 0.5);
	viewport->vp_w = viewport->aspect_ratio * viewport->vp_h;
	viewport->step_w = viewport->vp_w * INV_WIN_WIDTH;
	viewport->step_h = viewport->vp_h * INV_WIN_HEIGHT;
}

static inline t_vect3	get_ray(int x, int y, t_viewport *viewport,
	t_cam_data *cam)
{
	double	u;
	double	v;

	u = (2.0 * (x + 0.5) * INV_WIN_WIDTH - 1.0) * viewport->aspect_ratio
		* viewport->tan_theta;
	v = (1.0 - 2.0 * (y + 0.5) * INV_WIN_HEIGHT) * viewport->tan_theta;
	return (vector_norm(vectors_add(cam->forward,
				vectors_add(vector_mult(cam->right, u), vector_mult(cam->up,
						v)))));
}

static inline float	check_object_collision(t_object *object, float t, t_vect3
	ray,
		t_vect3 cam_pos)
{
	float	new_t;

	if (object->e_type == _sphere)
		new_t = sphere_collision(ray, object, cam_pos);
	else if (object->e_type == _cylinder)
		return (t);
	else if (object->e_type == _plane)
		return (t);
	else if (object->e_type == _light)
		return (t);
	else
		return (t);
	if (new_t != -1 && (t == -1 || new_t < t))
		return (new_t);
	return (t);
}

int	get_pixel_color(t_vect3 ray, t_world_data *world)
{
	int		color;
	int		i;
	float	t;
	float	new_t;
	int		closest_obj_index;

	i = -1;
	t = -1;
	color = world->ambient_light.color;
	while (++i < world->obj_count)
	{
		new_t = check_object_collision(&world->objs[i], t, ray, world->cam.pos);
		if (new_t != -1 && (t == -1 || new_t < t))
		{
			color = world->objs[i].color;
			t = new_t;
			closest_obj_index = i;
		}
	}
	if (t == -1)
		return (color);
	return (shading(ray, cam_pos, t, objects[closest_obj_index], world));
}

void	render_canva(t_vect2 start, t_vect2 end, t_world_data *world,
		t_mlx_data *mlx)
{
	t_vect2	pointer;
	t_vect3	ray;

	pointer.y = start.y;
	while (pointer.y <= end.y)
	{
		pointer.x = start.x;
		while (pointer.x <= end.x)
		{
			ray = get_ray(pointer.x, pointer.y, &world->viewport, &world->cam);
			my_mlx_pixel_put(mlx, pointer, /*color_sup(*/ get_pixel_color(ray,
					world) /*,
					get_prev_color(pointer, mlx))*/);
			pointer.x++;
		}
		pointer.y++;
	}
}
