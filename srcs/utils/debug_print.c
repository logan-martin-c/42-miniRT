/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:30:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 16:29:54 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sphere(t_sphere *sphere)
{
	t_color	color;

	color = parse_color(sphere->color);
	printf("Sphere :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)sphere->pos.x / 1000);
	printf("\t\ty : %lf\n", (double)sphere->pos.y / 1000);
	printf("\t\tz : %lf\n", (double)sphere->pos.z / 1000);
	printf("\tdiameter : %f\n", (float)sphere->diameter / 1000);
	printf("\tcolor:\n");
	printf("\t\ta : %u\n", color.alpha);
	printf("\t\tr : %u\n", color.red);
	printf("\t\tg : %u\n", color.green);
	printf("\t\tb : %u\n", color.blue);
}

void	print_plane(t_plane *plane)
{
	t_color	color;

	color = parse_color(plane->color);
	printf("Plane :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)plane->pos.x / 1000);
	printf("\t\ty : %lf\n", (double)plane->pos.y / 1000);
	printf("\t\tz : %lf\n", (double)plane->pos.z / 1000);
	printf("\tvector :\n");
	printf("\t\tx : %lf\n", (double)plane->rot.x / NORM_PREC);
	printf("\t\ty : %lf\n", (double)plane->rot.y / NORM_PREC);
	printf("\t\tz : %lf\n", (double)plane->rot.z / NORM_PREC);
	printf("\tcolor:\n");
	printf("\t\ta : %u\n", color.alpha);
	printf("\t\tr : %u\n", color.red);
	printf("\t\tg : %u\n", color.green);
	printf("\t\tb : %u\n", color.blue);
}

void	print_cylinder(t_cylinder *cylinder)
{
	t_color	color;

	color = parse_color(cylinder->color);
	printf("Cylinder :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)cylinder->pos.x / 1000);
	printf("\t\ty : %lf\n", (double)cylinder->pos.y / 1000);
	printf("\t\tz : %lf\n", (double)cylinder->pos.z / 1000);
	printf("\tvector :\n");
	printf("\t\tx : %lf\n", (double)cylinder->rot.x / NORM_PREC);
	printf("\t\ty : %lf\n", (double)cylinder->rot.y / NORM_PREC);
	printf("\t\tz : %lf\n", (double)cylinder->rot.z / NORM_PREC);
	printf("\tdiameter : %f\n", (float)cylinder->diameter / 1000);
	printf("\theight : %f\n", (float)cylinder->height / 1000);
	printf("\tcolor:\n");
	printf("\t\ta : %u\n", color.alpha);
	printf("\t\tr : %u\n", color.red);
	printf("\t\tg : %u\n", color.green);
	printf("\t\tb : %u\n", color.blue);
}

void	print_cam(t_cam_data *cam)
{
	printf("Camera :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)cam->pos.x / 1000);
	printf("\t\ty : %lf\n", (double)cam->pos.y / 1000);
	printf("\t\tz : %lf\n", (double)cam->pos.z / 1000);
	printf("\torientation :\n");
	printf("\t\tx : %lf\n", (double)cam->angle.x / NORM_PREC);
	printf("\t\ty : %lf\n", (double)cam->angle.y / NORM_PREC);
	printf("\t\tz : %lf\n", (double)cam->angle.z / NORM_PREC);
	printf("\fFOV : %d\n", cam->fov);
}

void	print_light(t_light_data *light)
{
	t_color	color;

	color = parse_color(light->color);
	printf("Light :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)light->pos.x / 1000);
	printf("\t\ty : %lf\n", (double)light->pos.y / 1000);
	printf("\t\tz : %lf\n", (double)light->pos.z / 1000);
	printf("\tratio : %f\n", (float)light->ratio / 255);
	printf("\tcolor:\n");
	printf("\t\ta : %u\n", color.alpha);
	printf("\t\tr : %u\n", color.red);
	printf("\t\tg : %u\n", color.green);
	printf("\t\tb : %u\n", color.blue);
}

void	print_ambient_light(t_ambient_light_data *ambient_light)
{
	t_color	color;

	color = parse_color(ambient_light->color);
	printf("Ambient light :\n");
	printf("\tratio : %f\n", (float)ambient_light->ratio / 255);
	printf("\tcolor:\n");
	printf("\t\ta : %u\n", color.alpha);
	printf("\t\tr : %u\n", color.red);
	printf("\t\tg : %u\n", color.green);
	printf("\t\tb : %u\n", color.blue);
}

void	print_nodes(t_parsing_data *p_data, t_world_data *world)
{
	t_list	*obj_lst;

	printf("Total : %d\n\n", p_data->obj_count);
	obj_lst = p_data->obj_lst;
	while (obj_lst)
	{
		if (((t_object *)(obj_lst->content))->e_type == _sphere)
			print_sphere(((t_object *)(obj_lst->content))->data);
		else if (((t_object *)(obj_lst->content))->e_type == _plane)
			print_plane(((t_object *)(obj_lst->content))->data);
		else if (((t_object *)(obj_lst->content))->e_type == _cylinder)
			print_cylinder(((t_object *)(obj_lst->content))->data);
		obj_lst = obj_lst->next;
	}
	print_cam(&world->cam);
	print_light(&world->light);
	print_ambient_light(&world->ambient_light);
}
