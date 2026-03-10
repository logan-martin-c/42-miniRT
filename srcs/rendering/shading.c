/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:24:58 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/10 16:06:26 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
//
#include "refraction.h"
#include "vectors_maths_3.h"
#include "vectors_maths_4.h"
//
#include "cone_collision.h"
#include "cone_collision_2.h"
#include "cylinder_collision.h"
#include "object_collision_2.h"
//
#include "colors_maths.h"
#include "colors_maths_2.h"
#include "mlx_utils.h"
#include "object_collision.h"
#define _USE_MATH_DEFINES

void	ini_compute_dl(t_shader_compute *shader, t_vect3 point_r_c,
		t_object object, t_world_data *world)
{
	(void)object;
	shader->amb_rgb = world->ambient_light.color;
	shader->n_view_normal = vector_norm(vectors_sub(world->cam.pos, point_r_c));
	shader->final_pixel_color = (t_float_color){1, 0, 0, 0};
	shader->final_pixel_color = colors_mult(colors_scal(shader->amb_rgb,
				world->ambient_light.ratio), shader->obj_rgb);
	shader->shadow_origin = vectors_add(point_r_c,
			vector_mult(shader->n_point_normal, 0.001f));
}

void	prep_compute_dl(t_shader_compute *shader, t_vect3 point_r_c,
		t_world_data *world, int i)
{
	shader->light_ray_dir = vectors_sub(world->lights[i].pos, point_r_c);
	shader->light_ray_dist = vector_mag(shader->light_ray_dir)
		- world->lights[i].u_data.light.radius;
	shader->light_ray.dir = vector_norm(shader->light_ray_dir);
	shader->light_ray.origin = shader->shadow_origin;
	shader->dot_nl = dot_product(shader->n_point_normal, shader->light_ray.dir);
}

void	shadow_factor(t_shader_compute *shader, t_world_data *world,
		t_object light)
{
	t_vect3				rand_p_light;
	t_vect3				rand_light_dir;
	float				rand_light_dist;
	t_nearest_object	hit;
	int					i;

	shader->light_intensity_sum = (t_float_color){1, 1, 1, 1};
	rand_p_light = get_rand_p_light(light.pos, light.u_data.light.radius);
	rand_light_dir = vectors_sub(rand_p_light, shader->shadow_origin);
	rand_light_dist = vector_mag(rand_light_dir);
	shader->shadow_ray.origin = shader->shadow_origin;
	shader->shadow_ray.dir = vector_norm(rand_light_dir);
	i = -1;
	while (++i < world->obj_count)
	{
		hit = check_object_collision(&world->objs[i], shader->shadow_ray);
		if (hit.t > 0 && hit.t < rand_light_dist)
		{
			shader->light_intensity_sum
				= colors_mult(colors_scal(hit.obj->material.color,
						1.0f - hit.obj->material.color.a),
					shader->light_intensity_sum);
		}
	}
}

void	calc_shader(t_shader_compute *shader, t_world_data *world, int i)
{
	float	attenuation;

	attenuation = 1.0f / (shader->light_ray_dist * shader->light_ray_dist
			+ 1.0f);
	shader->light_rgb = world->lights[i].material.color;
	shader->intensity = world->lights[i].u_data.light.ratio
		* (world->lights[i].u_data.light.radius + 1) * 200 * shader->dot_nl
		* attenuation;
	shader->diffuse = colors_scal(colors_mult(shader->light_rgb,
				shader->obj_rgb), shader->intensity);
	shader->diffuse = colors_mult(shader->diffuse, shader->light_intensity_sum);
	shader->final_pixel_color = colors_add(shader->final_pixel_color,
			shader->diffuse);
}

t_float_color	compute_direct_light(t_nearest_object hit, t_world_data *world)
{
	t_shader_compute	shader;
	int					i;

	i = 0;
	shader.obj_rgb = get_texture_color(hit);
	shader.n_point_normal = hit.normal;
	ini_compute_dl(&shader, hit.collision_point, *hit.obj, world);
	while (i < world->light_count)
	{
		prep_compute_dl(&shader, hit.collision_point, world, i);
		if (shader.dot_nl > 0)
		{
			shadow_factor(&shader, world, world->lights[i]);
			calc_shader(&shader, world, i);
		}
		i++;
	}
	return (shader.final_pixel_color);
}
