/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:36:21 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/02 18:31:27 by adastugu         ###   ########.fr       */
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

static inline t_vect3	get_ray_dir(int x, int y, t_viewport *viewport,
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

int	get_pixel_color(t_ray ray, t_world_data *world, int bounce)
{
	t_nearest_object	nearest;
	t_vect3				normal;
	t_vect3				normal_diffused;
	t_vect3				collision_point;

	nearest.t = -1;
	if (bounce > BOUNCES)
		return (get_sky_color(color_intensity(world->ambient_light.color,
					world->ambient_light.ratio), ray.dir));
	nearest = get_nearest_object(ray, world);
	if (nearest.t == -1)
		return (get_sky_color(color_intensity(world->ambient_light.color,
					world->ambient_light.ratio), ray.dir));
	if (bounce + 1 > BOUNCES)
		return (color_gradient(nearest.obj->color,
				get_sky_color(color_intensity(world->ambient_light.color,
						world->ambient_light.ratio), ray.dir),
				nearest.obj->u_data.sphere.reflectance));
	collision_point = get_collision_point(ray, nearest.t - nearest.t * 1e-3);
	normal = sphere_normal(nearest.obj, collision_point, ray.dir);
	normal_diffused = get_diffuse_vector(normal, nearest.obj->u_data.sphere.reflectance);
	t_vect3	direct_rgb;
	t_vect3	indirect_rgb;
	t_vect3	final_rgb;
	direct_rgb = compute_direct_light(collision_point, normal, *nearest.obj, world);
	if (bounce < BOUNCES && nearest.obj->u_data.sphere.reflectance > 0)
	{
		ray.dir = vector_norm(reflect(ray.dir, normal_diffused));
		ray.origin = collision_point;
		indirect_rgb = color_to_vec3(color_gradient(nearest.obj->color, get_pixel_color(ray, world,
					bounce + 1), nearest.obj->u_data.sphere.reflectance));
	}
	final_rgb = vectors_add(direct_rgb, vector_mult (indirect_rgb, nearest.obj->u_data.sphere.reflectance));
	return (vec3_to_color(final_rgb));
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

void	render_canva(t_vect2 start, t_vect2 end, t_world_data *world,
		t_mlx_data *mlx)
{
	t_vect2	pointer;
	t_ray	ray;

	pointer.y = start.y;
	while (pointer.y <= end.y)
	{
		pointer.x = start.x;
		while (pointer.x <= end.x)
		{
			ray.dir = get_ray_dir(pointer.x, pointer.y, &world->viewport,
					&world->cam);
			ray.origin = world->cam.pos;
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
