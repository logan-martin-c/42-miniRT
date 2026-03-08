/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:41:28 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 18:43:35 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "map.h"

void	print_sphere(t_object *object);
void	print_plane(t_object *object);
void	print_cylinder(t_object *object);
void	print_cam(t_cam_data *cam);
void	print_light(t_object *object);
void	print_ambient_light(t_ambient_light_data *ambient_light);
void	print_json(t_json json_tokens, unsigned int indent);

#endif