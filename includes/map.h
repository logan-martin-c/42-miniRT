/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:38:51 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 12:39:22 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "minirt.h"
# include <stdbool.h>

typedef struct s_pos_xyz
{
	long			x;
	long			y;
	long			z;
	int				color;
}					t_pos_xyz;

typedef struct s_color
{
	unsigned char	alpha;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_color;

typedef struct s_key_status
{
	char			w;
	char			a;
	char			s;
	char			d;
	char			space;
	char			ctrl;
}					t_key_status;

typedef struct s_cam_data
{
	t_pos_xyz		pos;
	t_pos_xyz		move;
	t_pos_xyz		angle;
	int				fov;
	double			cos_x;
	double			sin_x;
	double			cos_z;
	double			sin_z;
	int				speed;
}					t_cam_data;

typedef struct s_light_data
{
	t_pos_xyz		pos;
	unsigned char	ratio;
	int				color;
}					t_light_data;

typedef struct s_ambient_light_data
{
	unsigned char	ratio;
	int				color;
}					t_ambient_light_data;

typedef struct s_map_data
{
	bool			cam;
	bool			ambient_light;
	bool			light;
}					t_map_data;

typedef struct s_object
{
	enum
	{
		//_ambient_lighting,
		//_camera,
		//_light,
		_sphere,
		_plane,
		_cylinder
	} e_type;
	void			*data;
}					t_object;

typedef struct s_ambient_lighting
{
	char			ratio;
	int				color;
}					t_ambient_lighting;

// typedef struct s_camera
// {
// 	t_pos_xyz		pos;
// 	t_pos_xyz		rot;
// 	int				fov;
// }					t_camera;

typedef struct s_sphere
{
	t_pos_xyz		pos;
	int				diameter;
	int				color;
}					t_sphere;

typedef struct s_plane
{
	t_pos_xyz		pos;
	t_pos_xyz		rot;
	int				color;
}					t_plane;

typedef struct s_cylinder
{
	t_pos_xyz		pos;
	t_pos_xyz		rot;
	int				diameter;
	int				height;
	int				color;
}					t_cylinder;

#endif