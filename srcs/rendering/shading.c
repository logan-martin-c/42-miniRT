/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:24:58 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/04 16:39:51 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "colors_maths.h"
#include "colors_maths_2.h"
#include "mlx_utils.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#include "vectors_maths_3.h"
#define _USE_MATH_DEFINES

void	ini_compute_dl(t_shader_compute *shader, t_vect3 point_r_c,
		t_object object, t_world_data *world)
{
	(void)object;
	shader->amb_rgb = world->ambient_light.color;
	//shader->obj_rgb = color_to_vec3(object.color);
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
	shader->light_ray_dist = vector_mag(shader->light_ray_dir);
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
	int					s;

	s = 0;
	shader->light_intensity_sum = 0;
	while (s < SAMPLES)
	{
		rand_p_light = get_rand_p_light(light.pos, light.u_data.light.radius);
		rand_light_dir = vectors_sub(rand_p_light, shader->shadow_origin);
		rand_light_dist = vector_mag(rand_light_dir);
		shader->shadow_ray.origin = shader->shadow_origin;
		shader->shadow_ray.dir = vector_norm(rand_light_dir);
		hit = get_nearest_object(shader->shadow_ray, world);
		if (hit.t < 0 || hit.t > rand_light_dist)
			shader->light_intensity_sum += 1.0f;
		s++;
	}
	shader->light_intensity_sum = shader->light_intensity_sum / (float)SAMPLES;
}

t_float_color	compute_direct_light(t_vect3 point_r_c, t_vect3 point_normal,
		t_object object, t_world_data *world)
{
	t_shader_compute	shader;
	int					i;

	i = 0;
	shader.n_point_normal = vector_norm(point_normal);
	shader.obj_rgb = get_texture_color(point_r_c, object);
	ini_compute_dl(&shader, point_r_c, object, world);
	while (i < world->light_count)
	{
		//printf("a: %f, r: %f, g: %f, b: %f, x: %f, y: %f, z: %f, ratio: %f\n", world->lights[i].color.a, world->lights[i].color.r, world->lights[i].color.g, world->lights[i].color.b, world->lights[i].pos.x, world->lights[i].pos.y, world->lights[i].pos.z, world->lights[i].u_data.light.ratio);
		prep_compute_dl(&shader, point_r_c, world, i);
		if (shader.dot_nl > 0)
		{
			shadow_factor(&shader, world, world->lights[i]);
			shader.light_rgb = world->lights[i].material.color;
			shader.intensity = world->lights[i].u_data.light.ratio * shader.dot_nl;
			shader.diffuse = colors_scal(colors_mult(shader.light_rgb,
						shader.obj_rgb), shader.intensity);
			shader.diffuse = colors_scal(shader.diffuse,
					shader.light_intensity_sum);
			shader.final_pixel_color = colors_add(shader.final_pixel_color,
					shader.diffuse);
		}
		i++;
	}
	return (shader.final_pixel_color);
}

/* void	compute_direct_specular(t_shader_compute *shader, t_world_data *world,
		int i)
{
	t_vect3	point_ray_colision;
	t_vect3	point_normal;
	t_float_color	obj_splt_colors;
	t_vect3	n;

	shader->neg_light_normal = vector_norm(vector_mult(shader->light_ray_dir,
				-1.0));
	shader->reflection_direction = vector_reflect(shader->neg_light_normal,
			shader->n_point_normal_diffused);
	shader->dot_rv = ft_max_float(0.0f,
			dot_product(shader->reflection_direction, shader->n_view_normal));
	shader->spec_power = pow(shader->dot_rv, 32);
	shader->specular = vector_mult(vector_mult(shader->light_rgb,
				world->lights[i].ratio), shader->spec_power);
} */
/* /// @brief calc P space pos, calc P normal, calc direct light intensity,
	return adjusted color
t_vect3	shading(t_vect3 ray, t_nearest_object nearest, t_world_data *world)
{
	point_ray_colision = get_p_pos(ray, world->cam.pos, nearest.t);
	point_normal = get_p_normal(*(nearest.obj), point_ray_colision);
	//n = vector_norm(n);
	return (compute_direct_light(point_ray_colision, point_normal,
			*(nearest.obj), world));
} */
/* int apply_lighting(int o_color, float intensity)
{
	obj_splt_colors = parse_color(o_color);
	obj_splt_colors.red *= intensity;
	obj_splt_colors.green *= intensity;
	obj_splt_colors.blue *= intensity;
	return (get_color(obj_splt_colors));
} */
/* t_vect3	get_p_normal(t_object object, t_vect3 p)
{
	n.x = p.x - object.pos.x;
	n.y = p.y - object.pos.y;
	n.z = p.z - object.pos.z;
	return (n);
}

t_vect3	get_p_pos(t_vect3 ray, t_vect3 cam_pos, float t)
{
	t_vect3	p;

	p.x = cam_pos.x + t * ray.x;
	p.y = cam_pos.y + t * ray.y;
	p.z = cam_pos.z + t * ray.z;
	return (p);
} */