/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:38:51 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/09 13:28:27 by adastugu         ###   ########.fr       */
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

typedef struct s_uv
{
	float			u;
	float			v;
}					t_uv;

typedef struct s_ray
{
	t_vect3			origin;
	t_vect3			dir;
	float			origin_refraction;
	enum
	{
		_reflected,
		_refracted
	} blend_mode;
}					t_ray;

typedef struct s_float_color
{
	float			a;
	float			r;
	float			g;
	float			b;
}					t_float_color;

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
	int				speed;
	int				fov;
	double			cos_pitch;
	double			sin_pitch;
	double			cos_yaw;
	double			sin_yaw;
	t_vect3			pos;
	t_vect3			forward;
	t_vect3			right;
	t_vect3			up;
}					t_cam_data;

typedef struct s_ambient_light_data
{
	float			ratio;
	t_float_color	color;
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
}					t_sphere;

typedef struct s_cylinder
{
	float			radius;
	float			height;
}					t_cylinder;

typedef struct s_cone
{
	float			radius;
	float			height;
}					t_cone;

typedef struct s_light
{
	float			ratio;
	float			radius;
}					t_light;

typedef struct s_texture
{
	void			*img;
	int				*pixels;
	int				width;
	int				height;
}					t_texture;

typedef struct s_material
{
	char *tex_name;
	char *normal_name;
	float			reflectance;
	float			smoothness;
	float			refraction;
	t_float_color	color;
	t_texture		tex;
	t_texture		normal;
}					t_material;

typedef struct s_object
{
	enum
	{
		_sphere,
		_plane,
		_cylinder,
		_cone,
		_light
	} e_type;
	t_material		material;
	t_vect3			pos;
	t_vect3			rot;
	union
	{
		t_sphere	sphere;
		t_cylinder	cylinder;
		t_cone		cone;
		t_light		light;
	} u_data;
}					t_object;

#endif