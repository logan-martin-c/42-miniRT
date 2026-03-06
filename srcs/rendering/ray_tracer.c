/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:36:21 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/06 16:14:42 by adastugu         ###   ########.fr       */
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
#include "vectors_maths_2.h"
#include "vectors_maths_3.h"
#include "vectors_maths_4.h"
#include "refraction.h"
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
	t_vect3				normal;
	//t_vect3				normal_diffused;
	t_vect3				collision_point;
	//bool				direction;

	if (bounce > BOUNCES)
		return (BLACK);
	nearest = get_nearest(ray, world);
	if (nearest.t == -1)
		return (get_sky_color(color_intensity(world->ambient_light.color,
					world->ambient_light.ratio), ray.dir));
	if (nearest.obj->e_type == _light)
		return (colors_scal(nearest.obj->color, 2.0f));

	collision_point = get_collision_point(ray, nearest.t);
	normal = nearest.normal;
	//normal_diffused = get_diffuse_vector(normal, nearest.obj->reflectance);

	// // might no need this because its better calc at collision and stored in nearest/hit
	// if (dot_product(normal, ray.dir) < 0)
    //     direction = false;
	// else
   	// 	direction = true;

	float n1 = ray.origin_refraction;
	float n2;

	if (nearest.is_inside)
			n2 = 1.0f;
	else
			n2 = nearest.obj->refraction;
	
	ray.dir = get_bounce_2(ray, nearest, n1, n2);
	ray.origin_refraction = n2;

	if (dot_product(ray.dir, nearest.normal) > 0)
			ray.origin = vectors_add(collision_point, vector_mult(nearest.normal, 0.001f));
	else
			ray.origin = vectors_sub(collision_point, vector_mult(nearest.normal, 0.001f));

	t_float_color	direct_rgb;
	t_float_color	indirect_rgb = BLACK;
	t_float_color	final_rgb;
	t_float_color	obj_rgb = get_texture_color(collision_point, *nearest.obj);

	

	/* if (direction)
		ray.dir = get_bounce(ray, normal_diffused, obj_rgb, get_current_refraction(world->objs, world->obj_count, collision_point));
	else
		ray.dir = get_bounce(ray, normal_diffused, obj_rgb, nearest.obj->u_data.sphere.refraction);
	ray.origin = collision_point;
	if (direction)
		ray.origin_refraction = get_current_refraction(world->objs, world->obj_count, collision_point);
	else
		ray.origin_refraction = nearest.obj->u_data.sphere.refraction; */
		
	
	if (nearest.obj->color.a < 1.0f)
    {
        // Get light from through/off the glass
        t_float_color indirect = get_pixel_color(ray, world, bounce + 1);
        // Get the "surface" lighting (highlights and shadows on the glass)
        t_float_color direct = compute_direct_light(collision_point, normal, *nearest.obj, world);

        // Mix: Alpha=0.9 is almost opaque (milky), Alpha=0.1 is almost clear.
        return colors_add(
            colors_scal(direct, nearest.obj->color.a),
            colors_scal(colors_mult(obj_rgb, indirect), 1.0f - nearest.obj->color.a)
        );
    }
	indirect_rgb = get_pixel_color(ray, world, bounce + 1);
	t_float_color indirect_part = colors_mult(obj_rgb, indirect_rgb);
	
	direct_rgb = compute_direct_light(collision_point, normal, *nearest.obj, world);
	float diffuse_weight = (1.0f - nearest.obj->reflectance) * nearest.obj->color.a;
	final_rgb = colors_add(colors_scal(direct_rgb, diffuse_weight), indirect_part);
	
	return (final_rgb);
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
				my_mlx_pixel_put(mlx, pointer, get_color_summed_2(pointer,
						world->color_tab, (get_pixel_color(ray, world, 0)),
						world->static_frames));
			else
				my_mlx_pixel_put(mlx, pointer, vec4_to_color(get_pixel_color(ray, world, 0)));
			pointer.x++;
		}
		pointer.y++;
	}
}
