/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:30:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/12 14:51:04 by lomartin         ###   ########.fr       */
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
	printf("\tdiameter : %d\n", sphere->diameter);
	printf("\tcolor:\n");
	printf("\t\ta : %u\n", color.alpha);
	printf("\t\tr : %u\n", color.red);
	printf("\t\tg : %u\n", color.green);
	printf("\t\tb : %u\n", color.blue);
}

void	print_cam(t_camera *cam)
{
	printf("Camera :\n");
	printf("\tpos :\n");
	printf("\t\tx : %lf\n", (double)cam->pos.x / 1000);
	printf("\t\ty : %lf\n", (double)cam->pos.y / 1000);
	printf("\t\tz : %lf\n", (double)cam->pos.z / 1000);
	printf("\torientation :\n");
	printf("\t\tx : %lf\n", (double)cam->rot.x / 1000);
	printf("\t\ty : %lf\n", (double)cam->rot.y / 1000);
	printf("\t\tz : %lf\n", (double)cam->rot.z / 1000);
	printf("\fFOV : %d\n", cam->fov);
}

void	print_nodes(t_parsing_data *p_data)
{
	t_list	*obj_lst;

	printf("Total : %d\n\n", p_data->obj_count);
	obj_lst = p_data->obj_lst;
	while (obj_lst)
	{
		if (((t_object *)(obj_lst->content))->e_type == _sphere)
			print_sphere(((t_object *)(obj_lst->content))->data);
		if (((t_object *)(obj_lst->content))->e_type == _camera)
			print_cam(((t_object *)(obj_lst->content))->data);
		obj_lst = obj_lst->next;
	}
}
