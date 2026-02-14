/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_params_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:41:08 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 18:41:23 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
