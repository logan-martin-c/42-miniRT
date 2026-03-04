/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:36:21 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/04 13:38:37 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "colors_maths.h"
#include "colors_maths_long.h"
#include "mlx_utils.h"
#include "object_collision.h"
#include "object_normal.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include "vectors_maths_3.h"
#include "refraction.h"
#define _USE_MATH_DEFINES
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

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

int	get_pixel_color(t_ray ray, t_world_data *world, int bounce)
{
	t_nearest_object	nearest;
	t_vect3				normal;
	t_vect3				normal_diffused;
	t_vect3				collision_point;
	bool				direction;

	if (bounce > BOUNCES)
		return (get_sky_color(color_intensity(world->ambient_light.color,
					world->ambient_light.ratio), ray.dir));
	nearest = get_nearest_obj_or_light(ray, world);
	if (nearest.t == -1)
		return (get_sky_color(color_intensity(world->ambient_light.color,
					world->ambient_light.ratio), ray.dir));
	if (nearest.type == _obj_light)
				return (vec3_to_color(vector_mult(color_to_vec3( nearest.u_data.light->color), 10.0f)));
	if (bounce + 1 > BOUNCES)
		return (color_gradient(nearest.u_data.obj->color,
				get_sky_color(color_intensity(world->ambient_light.color,
						world->ambient_light.ratio), ray.dir),
				nearest.u_data.obj->u_data.sphere.reflectance));
	collision_point = get_collision_point(ray, nearest.t - nearest.t * 1e-3);
	normal = sphere_normal(nearest.u_data.obj, collision_point, ray.dir);
	normal_diffused = get_diffuse_vector(normal, nearest.u_data.obj->u_data.sphere.reflectance);
	t_vect3	direct_rgb;
	t_vect3	indirect_rgb;
	t_vect3	final_rgb;
	direct_rgb = compute_direct_light(collision_point, normal, *nearest.u_data.obj, world);
	if (bounce < BOUNCES && nearest.u_data.obj->u_data.sphere.reflectance > 0)
	{
		ray.dir = vector_norm(reflect(ray.dir, normal_diffused));
		ray.origin = collision_point;
		indirect_rgb = color_to_vec3(color_gradient(nearest.u_data.obj->color, get_pixel_color(ray, world,
					bounce + 1), nearest.u_data.obj->u_data.sphere.reflectance));
	}
	float diffuse_weight = 1.0f - nearest.u_data.obj->u_data.sphere.reflectance;
	final_rgb = vectors_add(vector_mult (direct_rgb, diffuse_weight), vector_mult (indirect_rgb, nearest.u_data.obj->u_data.sphere.reflectance));
	return (vec3_to_color(final_rgb));
		return (BLACK);
	nearest = get_nearest_object(ray, world);
	if (nearest.t == -1)
		return (get_sky_color(color_intensity(world->ambient_light.color,
				world->ambient_light.ratio), ray.dir));
	collision_point = get_collision_point(ray, nearest.t);
	normal = sphere_normal(nearest.obj, collision_point, ray.dir, &direction);
	normal = get_diffuse_vector(normal, nearest.obj->u_data.sphere.reflectance);
	if (direction)
		ray.dir = get_bounce(ray, normal, nearest.obj->color, get_current_refraction(world->objs, world->obj_count, collision_point));
	else
		ray.dir = get_bounce(ray, normal, nearest.obj->color, nearest.obj->u_data.sphere.refraction);
	ray.origin = collision_point;
	if (direction)
		ray.origin_refraction = get_current_refraction(world->objs, world->obj_count, collision_point);
	else
		ray.origin_refraction = nearest.obj->u_data.sphere.refraction;
	return (color_gradient(nearest.obj->color, get_pixel_color(ray, world,
				bounce + 1), nearest.obj->u_data.sphere.reflectance));
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
						world->color_tab, get_pixel_color(ray, world, 0),
						world->static_frames));
			else
				my_mlx_pixel_put(mlx, pointer, get_pixel_color(ray, world, 0));
			pointer.x++;
		}
		pointer.y++;
	}
}

// int	get_pixel_color(t_ray ray, t_world_data *world)
// {
// 	t_nearest_object	nearest;


// 	nearest = get_nearest_object(ray, world);
// 	if (nearest.t == -1)
// 		return (get_sky_color(color_intensity(world->ambient_light.color,
// 					world->ambient_light.ratio), ray.dir));
// 	direct_rgb = shading(ray.dir, nearest, world );

// 	indirect_rgb = color_to_vec3(indirect_lighting(ray, world, 0));

// 	final_rgb = vectors_add(direct_rgb, vector_mult (indirect_rgb, nearest.obj->u_data.sphere.reflectance));
// 	return (vec3_to_color(final_rgb));

// }