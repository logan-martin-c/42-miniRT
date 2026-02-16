/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_obj_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:40:19 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/15 23:43:01 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sphere(t_sphere *sphere)
{
	t_color	color;

	color = parse_color(sphere->color);
	printf("Sphere :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)sphere->pos.x);
	printf("\t\ty : %lf\n", (double)sphere->pos.y);
	printf("\t\tz : %lf\n", (double)sphere->pos.z);
	printf("\tdiameter : %f\n", (float)sphere->diameter);
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
	printf("\t\tx : %lf\n", (double)plane->pos.x);
	printf("\t\ty : %lf\n", (double)plane->pos.y);
	printf("\t\tz : %lf\n", (double)plane->pos.z);
	printf("\tvector :\n");
	printf("\t\tx : %lf\n", (double)plane->rot.x);
	printf("\t\ty : %lf\n", (double)plane->rot.y);
	printf("\t\tz : %lf\n", (double)plane->rot.z);
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
	printf("\t\tx : %lf\n", (double)cylinder->pos.x);
	printf("\t\ty : %lf\n", (double)cylinder->pos.y);
	printf("\t\tz : %lf\n", (double)cylinder->pos.z);
	printf("\tvector :\n");
	printf("\t\tx : %lf\n", (double)cylinder->rot.x);
	printf("\t\ty : %lf\n", (double)cylinder->rot.y);
	printf("\t\tz : %lf\n", (double)cylinder->rot.z);
	printf("\tdiameter : %f\n", (float)cylinder->diameter);
	printf("\theight : %f\n", (float)cylinder->height);
	printf("\tcolor:\n");
	printf("\t\ta : %u\n", color.alpha);
	printf("\t\tr : %u\n", color.red);
	printf("\t\tg : %u\n", color.green);
	printf("\t\tb : %u\n", color.blue);
}
