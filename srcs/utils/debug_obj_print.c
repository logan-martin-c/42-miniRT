/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_obj_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:40:19 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 18:41:15 by lomartin         ###   ########.fr       */
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
