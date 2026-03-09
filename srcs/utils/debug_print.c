/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:30:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 23:07:22 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
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
		else if (((t_object *)(obj_lst->content))->e_type == _light)
			print_light(obj_lst->content);
		obj_lst = obj_lst->next;
	}
	print_cam(&world->cam);
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
	array = world->lights;
	obj_count = -1;
	while (++obj_count < world->light_count)
		print_light(&array[obj_count]);
	print_cam(&world->cam);
	print_ambient_light(&world->ambient_light);
}

void	print_indent(unsigned int indent)
{
	unsigned int	i;

	i = -1;
	while (++i < indent)
		printf("\t");
}

void	print_brace(t_json token, unsigned int indent)
{
	unsigned int	i;

	i = -1;
	printf("\n");
	print_indent(indent);
	printf("{\n");
	while (++i < token.u_data.s_brace.size)
	{
		if (i)
			printf(",\n");
		print_indent(indent + 1);
		print_json((t_json){.e_type = _string,
			.u_data.str = token.u_data.s_brace.data[i].key}, indent + 1);
		printf(": ");
		print_json(token.u_data.s_brace.data[i].value, indent + 1);
	}
	printf("\n");
	print_indent(indent);
	printf("}");
}

void	print_json(t_json token, unsigned int indent)
{
	unsigned int	i;

	if (token.e_type == _string)
		printf("\"%s\"", token.u_data.str);
	else if (token.e_type == _float)
		printf("%f", token.u_data.num);
	else if (token.e_type == _array)
	{
		printf("[");
		i = -1;
		while (++i < token.size)
		{
			printf("%f", token.u_data.array[i]);
			if (i + 1 < token.size)
				printf(", ");
		}
		printf("]");
	}
	else if (token.e_type == _brace)
		print_brace(token, indent);
}
