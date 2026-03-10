/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:21:42 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/10 13:40:43 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "map.h"
# include "mlx.h"
# include "settings.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

// KEYCODES
# define ESC 65307
# define L_ARROW 65361
# define U_ARROW 65362
# define R_ARROW 65363
# define D_ARROW 65364
# define C_KEY 99
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define I_KEY 105
# define SPACE_KEY 32
# define CTRL_KEY 65507
# define P_KEY 112
# define PLUS_KEY 61
# define MINUS_KEY 45
# define LEFT_BRACE 91
# define RIGHT_BRACE 93
# define QUOTE 39
# define COLON 59

# define LINE_SIZE 5120
# define BPP 4
# define INV_WIN_HEIGHT 0.0013888889
# define INV_WIN_WIDTH 0.00078125

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct s_tasks
{
	t_vect2					start;
	t_vect2					end;
}							t_tasks;

typedef struct s_long_color
{
	unsigned long			a;
	unsigned long			r;
	unsigned long			g;
	unsigned long			b;
}							t_long_color;

typedef struct s_int_color
{
	int						a;
	int						r;
	int						g;
	int						b;
}							t_int_color;

typedef struct s_mlx_data
{
	void					*mlx;
	void					*win;
	struct
	{
		char				*addr;
		int					bits_per_pixel;
		int					line_length;
		int					endian;
		void				*img;
	} s_img_data;
}							t_mlx_data;

typedef struct s_viewport
{
	double					aspect_ratio;
	double					theta;
	double					tan_theta;
	double					ratio_tan_theta;
	double					vp_h;
	double					vp_w;
	double					step_h;
	double					step_w;
	t_vect3					down;
	t_vect3					right;
}							t_viewport;

typedef struct s_world_data
{
	bool					moving;
	bool					rotating;
	int						obj_count;
	int						light_count;
	long					static_frames;
	t_object				*objs;
	t_object				*selected_obj;
	t_object				*lights;
	t_cam_data				cam;
	t_ambient_light_data	ambient_light;
	t_viewport				viewport;
	t_float_color			*color_tab;
}							t_world_data;

typedef struct s_json
{
	enum
	{
		_string,
		_float,
		_array,
		_brace
	} e_type;
	union
	{
		char				*str;
		float				num;
		float				array[4];
		struct
		{
			struct s_pair	*data;
			size_t			size;
		} s_brace;
	} u_data;
	size_t					size;
}							t_json;

typedef struct s_pair
{
	char					*key;
	t_json					value;
}							t_pair;

typedef enum e_file_type
{
	_rt,
	_json
}							t_file_type;

typedef struct s_parsing_data
{
	int						map_fd;
	int						obj_count;
	int						light_count;
	int						node_count;
	int						line_nb;
	t_file_type				file_type;
	FILE					*stream;
	t_list					*obj_lst;
	t_map_data				map_data;
	t_json					json;
}							t_parsing_data;

typedef enum e_obj_type
{
	_obj_object,
	_obj_param,
	_obj_light,
	_obj_none,
}							t_obj_type;

typedef struct s_nearest_object
{
	bool					is_inside;
	float					t;
	t_uv					uv;
	t_vect3					collision_point;
	float					current_refraction;
	t_object				*obj;
	t_vect3					normal;
	enum
	{
		_none,
		_body,
		_caps
	} e_hit_type;
}							t_nearest_object;

typedef struct s_interface
{
	bool					w;
	bool					a;
	bool					s;
	bool					d;
	bool					space;
	bool					ctrl;
}							t_interface;

typedef struct s_exec_data
{
	_Atomic bool			rendering;
	_Atomic bool			stop;
	_Atomic int				current_task;
	_Atomic int				tasks_done;
	_Atomic int				to_do;
	unsigned int			nb_threads;
	unsigned int			nb_tasks;
	pthread_mutex_t			mutex;
	pthread_t				*threads;
	t_tasks					*tasks;
}							t_exec_data;

typedef struct s_global_data
{
	char					*prog_name;
	t_mlx_data				mlx;
	t_interface				key;
	t_world_data			world;
	t_exec_data				*e_data;
}							t_global_data;

typedef struct s_shader_compute
{
	t_float_color			amb_rgb;
	t_float_color			obj_rgb;
	t_float_color			light_rgb;
	t_vect3					light_ray_dir;
	float					light_ray_dist;
	t_vect3					n_light_normal;
	t_vect3					n_point_normal;
	t_vect3					n_point_normal_diffused;
	t_vect3					n_view_normal;
	t_vect3					reflection_direction;
	t_vect3					neg_light_normal;
	t_vect3					shadow_origin;
	float					dot_nl;
	float					dot_rv;
	float					intensity;
	t_float_color			diffuse;
	float					spec_power;
	t_vect3					specular;
	t_float_color			final_pixel_color;
	t_nearest_object		shadow_t;
	t_ray					light_ray;
	t_float_color			light_intensity_sum;
	t_ray					shadow_ray;
}							t_shader_compute;

// INIT
void						init_texture(t_global_data *g_data);
void						init_normal(t_global_data *g_data);
int							init_mlx(t_mlx_data *mlx);
void						init(t_global_data *g_data, t_parsing_data *p_data,
								t_exec_data *e_data, char *av_zero);
void						init_viewport(t_viewport *viewport, int fov);

// PARSING
void						parser(int ac, char *av[], t_global_data *g_data,
								t_parsing_data *p_data);
void						check_args(int ac, char **av, char *prog_name,
								t_file_type *file_type);
int							open_map(char *filename, char *progname);
int							parse_pos(char *str, t_vect3 *pos, char normalized);
int							parse_raw_color(char *str, t_float_color *color);
int							parse_float(char *str, float *value);
t_float_color				parse_color(int color);
void						set_default_obj(t_object *obj);
void						parse_object(t_parsing_data *p_data, char *obj_line,
								t_global_data *g_data);
int							new_cone(t_parsing_data *p_data, char *obj_line,
								t_global_data *g_data, t_object *node);
void						parse_params(t_parsing_data *p_data, char *obj_line,
								t_global_data *g_data);
int							lst_map_to_array(t_parsing_data *p_data,
								t_world_data *world);
int							lst_objs_to_array(t_object **objs, t_list *obj_lst,
								int obj_count);
int							lst_lights_to_array(t_object **lights,
								t_list *obj_lst, int light_count);
void						parse_json(char *av[], t_global_data *g_data,
								t_parsing_data *p_data);

// RENDER
int							update_display(t_global_data *data);
int							get_color(t_float_color p_color);
t_float_color				get_color_chars(unsigned char a, unsigned char r,
								unsigned char g, unsigned char b);
t_float_color				compute_direct_light(t_nearest_object hit,
								t_world_data *world);
// int							color_sup(int color_a, int color_b);
t_vect3						project(t_vect3 pos, t_cam_data *cam_data);
// void						my_mlx_pixel_put(t_mlx_data *mlx, t_vect3 pos,
// 								int color);
void						trace_rays(t_world_data *world, t_mlx_data *mlx);
// t_vect3					vector_norm(t_vect3 a);
// t_vect3					vector_cross(t_vect3 a, t_vect3 b);
void						render_canva(t_vect2 start, t_vect2 end,
								t_world_data *world, t_mlx_data *mlx);
// int							get_prev_color(t_vect3 pos, t_mlx_data *mlx);
int							init_threads(t_exec_data *e_data,
								t_global_data *g_data);
int							init_exec(t_exec_data *e_data,
								t_global_data *g_data);
void						create_tasks(t_exec_data *e_data);
t_float_color				get_sky_color(t_float_color ambient_color,
								t_vect3 ray);
t_nearest_object			get_nearest_object(t_ray ray, t_world_data *world);
t_nearest_object			get_nearest(t_ray ray, t_world_data *world);
t_uv						get_uv_coords(t_nearest_object hit);
t_float_color				get_texture_color(t_nearest_object hit);
t_float_color				get_texel_color(t_texture tex, t_uv uv);
t_vect3						apply_normal_map(t_nearest_object hit);
t_float_color				get_pixel_color(t_ray ray, t_world_data *world,
								int bounce);

// INTERFACE
void						set_hooks(t_global_data *g_data);
void						move_cam(t_world_data *world, t_mlx_data *mlx,
								t_interface *key, int elapsed);
void						update_cam_pos(t_interface *input, t_cam_data *cam,
								int elapsed, bool *moving);
void						rotate_cam(t_cam_data *cam, t_mlx_data *mlx,
								bool *moving, t_object *obj);
void						set_moving_vector(bool moving, t_vect3 move,
								int elapsed);
t_vect3						get_lasting(void);
void						display_gui(t_world_data *world, t_mlx_data *mlx,
								int elapsed);
int							object_picker(int buttom, int x, int y, void *data);
int							move_object(t_object *obj, t_world_data *world,
								t_interface *input, int elapsed);
void						rotate_object(t_object *obj, t_vect2 move);

// UTILS
int							ft_puterr(char *error);
int							ft_error(char *error, char *progname);
int							ft_maperror(char *error, int line_nb,
								char *progname);
int							ft_perror(char *optional_name, char *progname);
char						*get_progname(char *av_zero);
unsigned long				get_time(unsigned long start);
unsigned long				get_utime(unsigned long start);
void						free_node(void *node);
void						clean_exit(int exit_status, t_global_data *g_data,
								t_parsing_data *p_data, t_exec_data *e_data);
int							win_close(t_global_data *g_data);
void						print_objects(t_parsing_data *p_data,
								t_world_data *world);
void						print_array(t_world_data *world);
int							check_args_count(char **args, unsigned int min,
								unsigned int max);
int							is_normalized(t_vect3 pos);
t_obj_type					get_obj_type(char *obj_line);

#endif
