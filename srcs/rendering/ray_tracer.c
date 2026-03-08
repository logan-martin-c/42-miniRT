/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:36:21 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/07 18:05:55 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "colors_maths.h"
#include "colors_maths_2.h"
#include "colors_maths_long.h"
#include "mlx_utils.h"
#include "object_collision.h"
#include "object_normal.h"
#include "vectors_maths_1.h"
#include "refraction.h"
#include "vectors_maths_2.h"
#include "vectors_maths_3.h"
#include "vectors_maths_4.h"
#include "refraction.h"
#include "tone_mapping.h"
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

static inline t_vect3	get_ray_dir(t_vect2 pos, t_viewport *viewport,
		t_cam_data *cam, bool moving)
{
	double	u;
	double	v;
	float	rx;
	float	ry;

	rx = 0.5;
	ry = 0.5;
	if (!moving)
	{
		rx = fast_rand();
		ry = fast_rand();
	}
	u = (2.0 * (pos.x + rx) * INV_WIN_WIDTH - 1.0) * viewport->aspect_ratio
		* viewport->tan_theta;
	v = (1.0 - 2.0 * (pos.y + ry) * INV_WIN_HEIGHT) * viewport->tan_theta;
	return (vector_norm(vectors_add(cam->forward,
				vectors_add(vector_mult(cam->right, u), vector_mult(cam->up,
						v)))));
}

t_float_color	get_pixel_color(t_ray ray, t_world_data *world, int bounce)
{
	t_nearest_object	nearest;
	//t_vect3				normal;
	t_vect3				normal_diffused;

	if (bounce > BOUNCES)
		return (BLACK);
	nearest = get_nearest(ray, world);
	if (nearest.t == -1)
		return (get_sky_color(color_intensity(world->ambient_light.color,
					world->ambient_light.ratio), ray.dir));
	if (nearest.obj->e_type == _light)
		return (colors_scal(nearest.obj->material.color, 10.0f));
	nearest.collision_point = get_collision_point(ray, nearest.t);
	nearest.uv = get_uv_coords(nearest);
	normal_diffused = get_diffuse_vector(nearest.normal, nearest.obj->material.smoothness);
	if (nearest.obj->normal_name && ft_strncmp(nearest.obj->normal_name, "error", 6))
		nearest.normal = apply_normal_map(nearest);

	
	t_float_color	direct_rgb;
	t_float_color	indirect_rgb;

	float diffuse_weight = (1.0 - nearest.obj->material.reflectance) * nearest.obj->material.color.a;

	direct_rgb = colors_scal(compute_direct_light(nearest, world), diffuse_weight);
	ray.dir = get_bounce(&ray, normal_diffused, nearest.obj->material, nearest.is_inside, world, nearest.collision_point);
	ray.origin = nearest.collision_point;
	if (nearest.is_inside)
		ray.origin_refraction = get_current_refraction(world->objs, world->obj_count, nearest.collision_point);
	else
		ray.origin_refraction = nearest.obj->material.refraction;
	if (ray.blend_mode == _reflected)
		indirect_rgb = color_gradient(direct_rgb, get_pixel_color(ray, world,
				bounce + 1), nearest.obj->material.reflectance);
	else
		indirect_rgb = colors_mult(nearest.obj->material.color, get_pixel_color(ray, world,bounce + 1));
	//indirect_rgb = color_correction(indirect_rgb);
	return (indirect_rgb);
}

void	render_canva(t_vect2 start, t_vect2 end, t_world_data *world,
		t_mlx_data *mlx)
{
	t_vect2	pointer;
	t_ray	ray;

	ray.origin = world->cam.pos;
	ray.origin_refraction = get_current_refraction(world->objs, world->obj_count, world->cam.pos);
	pointer.y = start.y;
	while (pointer.y <= end.y)
	{
		pointer.x = start.x;
		while (pointer.x <= end.x)
		{
			ray.dir = get_ray_dir(pointer, &world->viewport,
					&world->cam, world->moving || world->rotating);
			if (!world->moving && !world->rotating)
				my_mlx_pixel_put(mlx, pointer, get_color_summed(pointer,
						world->color_tab, (get_pixel_color(ray, world, 0)),
						world->static_frames));
			else
				my_mlx_pixel_put(mlx, pointer, vec4_to_color(get_pixel_color(ray, world, 0)));
			pointer.x++;
		}
		pointer.y++;
	}
}
