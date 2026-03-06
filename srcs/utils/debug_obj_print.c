/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_obj_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:40:19 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/06 12:04:33 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_sphere(t_object *object)
{
	printf("Sphere :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)object->pos.x);
	printf("\t\ty : %lf\n", (double)object->pos.y);
	printf("\t\tz : %lf\n", (double)object->pos.z);
	printf("\tdiameter : %f\n", (float)object->u_data.sphere.diameter);
	printf("\tcolor:\n");
	printf("\t\ta : %f\n", object->material.color.a);
	printf("\t\tr : %f\n", object->material.color.r);
	printf("\t\tg : %f\n", object->material.color.g);
	printf("\t\tb : %f\n", object->material.color.b);
	printf("\treflectance: %f\n", object->material.reflectance);
	printf("\trefraction: %f\n", object->material.refraction);
}

void	print_plane(t_object *object)
{
	printf("Plane :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)object->pos.x);
	printf("\t\ty : %lf\n", (double)object->pos.y);
	printf("\t\tz : %lf\n", (double)object->pos.z);
	printf("\tvector :\n");
	printf("\t\tx : %lf\n", (double)object->rot.x);
	printf("\t\ty : %lf\n", (double)object->rot.y);
	printf("\t\tz : %lf\n", (double)object->rot.z);
	printf("\tcolor:\n");
	printf("\t\ta : %f\n", object->material.color.a);
	printf("\t\tr : %f\n", object->material.color.r);
	printf("\t\tg : %f\n", object->material.color.g);
	printf("\t\tb : %f\n", object->material.color.b);
}

void	print_cylinder(t_object *object)
{
	printf("Cylinder :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)object->pos.x);
	printf("\t\ty : %lf\n", (double)object->pos.y);
	printf("\t\tz : %lf\n", (double)object->pos.z);
	printf("\tvector :\n");
	printf("\t\tx : %lf\n", (double)object->rot.x);
	printf("\t\ty : %lf\n", (double)object->rot.y);
	printf("\t\tz : %lf\n", (double)object->rot.z);
	printf("\tdiameter : %f\n", (float)object->u_data.cylinder.diameter);
	printf("\theight : %f\n", (float)object->u_data.cylinder.height);
	printf("\tcolor:\n");
	printf("\t\ta : %f\n", object->material.color.a);
	printf("\t\tr : %f\n", object->material.color.r);
	printf("\t\tg : %f\n", object->material.color.g);
	printf("\t\tb : %f\n", object->material.color.b);
}

void	print_light(t_object *object)
{
	printf("Light :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)object->pos.x);
	printf("\t\ty : %lf\n", (double)object->pos.y);
	printf("\t\tz : %lf\n", (double)object->pos.z);
	printf("\tratio : %f\n", (float)object->u_data.light.ratio);
	printf("\tcolor:\n");
	printf("\t\ta : %f\n", object->material.color.a);
	printf("\t\tr : %f\n", object->material.color.r);
	printf("\t\tg : %f\n", object->material.color.g);
	printf("\t\tb : %f\n", object->material.color.b);
}
