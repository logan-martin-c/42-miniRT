/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:37:04 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 23:00:20 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_H
# define JSON_H

typedef struct s_parsing_check
{
	bool	pos;
	bool	rot;
	bool	diamet;
	bool	height;
	bool	color;
	bool	refl;
	bool	refr;
	bool	smo;
	bool	tex;
	bool	bump;
	bool	ratio;
	bool	fov;
}			t_parsing_check;

typedef enum e_clamp_mode
{
	_ratio,
	_positive,
	_fov
}			t_clamp_mode;

// UTILS
float		ft_fatof(FILE *stream);
char		*get_string(FILE *stream, t_parsing_data *p_data,
				t_global_data *g_data);
int			lexer(t_json *dest, int *node_count, t_parsing_data *p_data,
				t_global_data *g_data);
void		free_json(t_json token);
int			json_to_array(t_parsing_data *p_data, t_global_data *g_data,
				t_world_data *world);

// ELEMENTS
int			new_pair(t_pair **pair, int *brace_size, t_parsing_data *p_data,
				t_global_data *g_data);
int			new_brace(t_json *dest, int *node_count, t_parsing_data *p_data,
				t_global_data *g_data);
int			new_float(t_json *dest, int *node_count, t_parsing_data *p_data,
				t_global_data *g_data);
int			new_string(t_json *dest, int *node_count, t_parsing_data *p_data,
				t_global_data *g_data);
int			new_array(t_json *dest, int *node_count, t_parsing_data *p_data,
				t_global_data *g_data);

// SUB_PARAMETERS
int			parse_json_pos(t_json *json, t_vect3 *pos, char normalized);
int			parse_json_raw_color(t_json *json, t_float_color *color);
int			parse_json_float(t_json *json, float *value, t_clamp_mode mode);
int			parse_json_string(t_json *json, char **value);
int			parse_json_material(t_pair *pair, t_parsing_check *check,
				t_material *material);

// OBJECTS
int			json_to_sphere(t_json json, t_global_data *g_data,
				t_world_data *world);
int			json_to_cylinder(t_json json, t_global_data *g_data,
				t_world_data *world);
int			json_to_plane(t_json json, t_global_data *g_data,
				t_world_data *world);
int			json_to_cone(t_json json, t_global_data *g_data,
				t_world_data *world);
int			json_to_light(t_json json, t_global_data *g_data,
				t_world_data *world);

// PARAMS
int			json_to_cam(t_json json, t_parsing_data *p_data,
				t_global_data *g_data, t_world_data *world);
int			json_to_a_light(t_json json, t_parsing_data *p_data,
				t_global_data *g_data, t_world_data *world);

#endif
