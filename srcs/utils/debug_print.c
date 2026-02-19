/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:30:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/17 09:32:47 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "debug.h"

void	print_objects(t_parsing_data *p_data, t_world_data *world)
{
	t_list	*obj_lst;

	printf("Total : %d\n\n", p_data->obj_count);
	obj_lst = p_data->obj_lst;
	while (obj_lst)
	{
		if (((t_object *)(obj_lst->content))->e_type == _sphere)
			print_sphere(obj_lst->content);
		else if (((t_object *)(obj_lst->content))->e_type == _plane)
			print_plane(obj_lst->content);
		else if (((t_object *)(obj_lst->content))->e_type == _cylinder)
			print_cylinder(obj_lst->content);
		obj_lst = obj_lst->next;
	}
	print_cam(&world->cam);
	print_light(&world->light);
	print_ambient_light(&world->ambient_light);
}

void	print_array(t_world_data *world)
{
	int			obj_count;
	t_object	*array;

	obj_count = -1;
	array = world->objs;
	printf("Total : %d\n\n", world->obj_count);
	while (++obj_count < world->obj_count)
	{
		if (array[obj_count].e_type == _sphere)
			print_sphere(&array[obj_count]);
		else if (array[obj_count].e_type == _plane)
			print_plane(&array[obj_count]);
		else if (array[obj_count].e_type == _cylinder)
			print_cylinder(&array[obj_count]);
	}
	print_cam(&world->cam);
	print_light(&world->light);
	print_ambient_light(&world->ambient_light);
}
