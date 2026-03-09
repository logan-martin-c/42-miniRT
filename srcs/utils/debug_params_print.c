/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_params_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:41:08 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/04 15:43:24 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_cam(t_cam_data *cam)
{
	printf("Camera :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)cam->pos.x);
	printf("\t\ty : %lf\n", (double)cam->pos.y);
	printf("\t\tz : %lf\n", (double)cam->pos.z);
	printf("\torientation :\n");
	printf("\t\tx : %lf\n", (double)cam->forward.x);
	printf("\t\ty : %lf\n", (double)cam->forward.y);
	printf("\t\tz : %lf\n", (double)cam->forward.z);
	printf("\tFOV : %d\n", cam->fov);
}

void	print_ambient_light(t_ambient_light_data *ambient_light)
{
	t_float_color	color;

	color = (ambient_light->color);
	printf("Ambient light :\n");
	printf("\tratio : %f\n", (float)ambient_light->ratio);
	printf("\tcolor:\n");
	printf("\t\ta : %f\n", color.a);
	printf("\t\tr : %f\n", color.r);
	printf("\t\tg : %f\n", color.g);
	printf("\t\tb : %f\n", color.b);
}
