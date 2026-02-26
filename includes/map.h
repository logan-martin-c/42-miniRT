/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:38:51 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/26 12:19:52 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "minirt.h"
# include <stdbool.h>

typedef struct s_vect3
{
	float			x;
	float			y;
	float			z;
}					t_vect3;

typedef struct s_vect2
{
	int				x;
	int				y;
}					t_vect2;

typedef struct s_ray
{
	t_vect3			origin;
	t_vect3			dir;
}					t_ray;

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
	t_vect3		pos;
	t_vect3		angle;
	int				fov;
	double			cos_pitch;
	double			sin_pitch;
	double			cos_yaw;
	double			sin_yaw;
	int				speed;
	t_vect3		forward;
	t_vect3		right;
	t_vect3		up;
}					t_cam_data;

typedef struct s_ambient_light_data
{
	float			ratio;
	int				color;
}					t_ambient_light_data;

typedef struct s_map_data
{
	bool			cam;
	bool			ambient_light;
}					t_map_data;

typedef struct s_sphere
{
	float			diameter;
	float			radius;
	float			reflectance;
}					t_sphere;

typedef struct s_cylinder
{
	float			diameter;
	float			height;
}					t_cylinder;

typedef struct s_light
{
	t_vect3			pos;
	float			ratio;
	int				color;
}					t_light;

typedef struct s_object
{
	enum
	{
		_sphere,
		_plane,
		_cylinder,
		_light
	} e_type;
	int				color;
	t_vect3		pos;
	t_vect3		rot;
	union
	{
		t_sphere	sphere;
		t_cylinder	cylinder;
		t_light		light;
	}				u_data;
}					t_object;

#endif