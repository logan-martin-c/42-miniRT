/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:30:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 18:44:57 by lomartin         ###   ########.fr       */
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
