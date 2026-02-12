/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:48:12 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/12 09:10:02 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	new_sphere(t_list **object_lst, char *obj_line, char *progname)
{
	t_sphere	*sphere;
	char		**params;
	char		**pos;

	sphere = malloc(sizeof(sphere));
	if (!sphere)
	{
		/* clean_exit(ft_perror(NULL, progname)) */;
	}
	params = ft_split_charset(obj_line, " \t\v\f\r");
	if (!params || !params[1] || !params[2] || !params[3] || params[4])
	{
		; // ERROR
	}
	if (parse_pos(params[1], &sphere->pos))
	{
		; // ERROR
	}
	sphere->diameter = ft_atof(params[2]);
	if (parse_raw_color(params[3], &sphere->color))
	{
		; // COLOR
	}
	printf("%ld\n", sphere->pos.x);
	printf("%ld\n", sphere->pos.y);
	printf("%ld\n", sphere->pos.z);
	printf("%d\n", sphere->diameter);
	printf("%u\n", (unsigned int)sphere->color);
	return (0);
}

void	parse_object(t_list **object_lst, char *obj_line, t_global_data *g_data)
{
	if (!ft_strncmp(obj_line, "C", 1) && ft_isspace(obj_line[1]))
	{
	}
	else if (!ft_strncmp(obj_line, "sp", 1) && ft_isspace(obj_line[2]))
		new_sphere(object_lst, obj_line, g_data->prog_name);
	else
	{
		ft_maperror("Invalid object type", g_data->prog_name);
		// FREE NODES
		exit(EXIT_FAILURE);
	}
}

int	parse_map(int map_fd, t_global_data *g_data)
{
	t_list	*obj_lst;
	char	*obj_line;

	obj_lst = NULL;
	obj_line = "";
	while (obj_line)
	{
		obj_line = get_next_line(map_fd);
		if (!obj_line)
			return (0);
		parse_object(&obj_lst, obj_line, g_data);
	}
}
