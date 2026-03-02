/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:24:58 by adastugu          #+#    #+#             */
/*   Updated: 2026/03/02 11:29:45 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
#include "colors_maths.h"
#include "mlx_utils.h"
#include "vectors_maths_1.h"
#include "vectors_maths_2.h"
#define _USE_MATH_DEFINES

t_vect3 get_p_normal(t_object object, t_vect3 p)
{
	t_vect3 n;

	n.x = p.x - object.pos.x;
	n.y = p.y - object.pos.y;
	n.z = p.z - object.pos.z;
	return (n);
}

t_vect3 get_p_pos(t_vect3 ray, t_vect3 cam_pos, float t)
{
	t_vect3 p;

	p.x = cam_pos.x + t * ray.x;
	p.y = cam_pos.y + t * ray.y;
	p.z = cam_pos.z + t * ray.z;
	return (p);
}

typedef struct s_shader_compute
{
	t_vect3 amb_rgb;
	t_vect3 obj_rgb;
	t_vect3 light_rgb;
	t_vect3 light_ray_dir;
	double light_ray_dist;
	t_vect3 n_light_normal;
	t_vect3 n_point_normal;
	t_vect3 n_view_normal;
	t_vect3 reflection_direction;
	t_vect3 neg_light_normal;
	float dot_nl;
	float dot_rv;
	float intensity;
	t_vect3 diffuse;
	float spec_power;
	t_vect3 specular;
	t_vect3 final_pixel_color;
	t_nearest_object shadow_t;
	t_ray light_ray;
} t_shader_compute;

void ini_compute_dl(t_shader_compute *shader, t_vect3 point_r_c, t_vect3 point_normal, t_object object ,t_world_data *world)
{
	shader->amb_rgb = color_to_vec3(world->ambient_light.color);
	shader->obj_rgb = color_to_vec3(object.color);
	shader->n_point_normal = vector_norm(point_normal);
	shader->n_view_normal = vector_norm(vectors_sub(world->cam.pos, point_r_c));
	shader->final_pixel_color = (t_vect3){0, 0, 0};
	shader->final_pixel_color = vectors_mult(vector_mult(shader->amb_rgb, world->ambient_light.ratio), shader->obj_rgb);
}

void compute_direct_specular(t_shader_compute *shader, t_world_data *world, int i)
{
	shader->neg_light_normal = vector_norm(vector_mult(shader->light_ray_dir, -1.0));
	shader->reflection_direction = vector_reflect(shader->neg_light_normal, shader->n_point_normal);
	shader->dot_rv = ft_max_float(0.0f, dot_product(shader->reflection_direction, shader->n_view_normal));
	shader->spec_power = pow(shader->dot_rv, 32);
	shader->specular = vector_mult(vector_mult(shader->light_rgb, world->lights[i].ratio), shader->spec_power);
}


t_vect3 compute_direct_light(t_vect3 point_r_c, t_vect3 point_normal, t_object object ,t_world_data *world)
{
    t_shader_compute shader;
    int i = 0;

    ini_compute_dl(&shader, point_r_c, point_normal, object , world);
    t_vect3 shadow_origin = vectors_add(point_r_c, vector_mult(shader.n_point_normal, 0.001f));
    while(i < world->light_count)
    {
        shader.light_ray_dir = vectors_sub(world->lights[i].pos, point_r_c);
        shader.light_ray_dist = vector_mag(shader.light_ray_dir);
        shader.light_ray.dir = vector_norm(shader.light_ray_dir);
        shader.light_ray.origin = shadow_origin;
        shader.shadow_t = get_nearest_object(shader.light_ray, world);
        if (shader.shadow_t.t > 0.001f && shader.shadow_t.t < shader.light_ray_dist)
        {
            i++;
            continue;
        }
        shader.dot_nl = dot_product(shader.n_point_normal, shader.light_ray.dir);
        if (shader.dot_nl > 0)
        {
            shader.light_rgb = color_to_vec3(world->lights[i].color);
            shader.intensity = world->lights[i].ratio * shader.dot_nl;
            shader.diffuse = vector_mult(vectors_mult(shader.light_rgb, shader.obj_rgb), shader.intensity);
            compute_direct_specular(&shader, world, i);
            shader.final_pixel_color = vectors_add(shader.final_pixel_color, vectors_add(shader.diffuse, shader.specular));
        }
        i++;
    }
    return (shader.final_pixel_color);
}

/// @brief calc P space pos, calc P normal, calc direct light intensity, return adjusted color
t_vect3 shading(t_vect3 ray, t_nearest_object nearest, t_world_data *world)
{
	t_vect3 point_ray_colision;
	t_vect3 point_normal;

	point_ray_colision = get_p_pos(ray, world->cam.pos, nearest.t);
	point_normal = get_p_normal(*(nearest.obj), point_ray_colision);
	//n = vector_norm(n);
	return (compute_direct_light(point_ray_colision, point_normal, *(nearest.obj), world));
	
}



/* int apply_lighting(int o_color, float intensity)
{
	t_color obj_splt_colors;

	obj_splt_colors = parse_color(o_color);
	obj_splt_colors.red *= intensity;
	obj_splt_colors.green *= intensity;
	obj_splt_colors.blue *= intensity;
	return (get_color(obj_splt_colors));
} */