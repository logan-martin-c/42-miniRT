/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adastugu <adastugu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:21:42 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/20 18:00:01 by adastugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "map.h"
# include "mlx.h"
# include "settings.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

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
# define SPACE_KEY 32
# define CTRL_KEY 65507
# define P_KEY 112
# define PLUS_KEY 65451
# define MINUS_KEY 65453

# define LINE_SIZE WIN_WIDTH * 4
# define BPP 4
# define BLACK 0xFF000000
# define INV_WIN_HEIGHT 1 / WIN_HEIGHT
# define INV_WIN_WIDTH 1 / WIN_WIDTH

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct s_mlx_data
{
	void					*mlx;
	void					*win;
	struct
	{
		void				*img;
		char				*addr;
		int					bits_per_pixel;
		int					line_length;
		int					endian;
	} s_img_data;
}							t_mlx_data;

typedef struct s_viewport
{
	t_vect3				down;
	t_vect3				right;
	double					aspect_ratio;
	double					theta;
	double					tan_theta;
	double					ratio_tan_theta;
	double					vp_h;
	double					vp_w;
	double					step_h;
	double					step_w;
}							t_viewport;

typedef struct s_world_data
{
	t_object				*objs;
	int						obj_count;
	bool					moving;
	bool					rotating;
	t_cam_data				cam;
	t_light_data			light;
	t_ambient_light_data	ambient_light;
	t_viewport				viewport;
}							t_world_data;

typedef struct s_parsing_data
{
	int						map_fd;
	t_list					*obj_lst;
	int						obj_count;
	t_map_data				map_data;
}							t_parsing_data;

typedef struct s_interface
{
	bool					w;
	bool					a;
	bool					s;
	bool					d;
	bool					space;
	bool					ctrl;
}							t_interface;

typedef struct s_global_data
{
	char					*prog_name;
	t_mlx_data				mlx;
	t_interface				key;
	t_world_data			world;
}							t_global_data;

typedef enum e_obj_type
{
	_obj_object,
	_obj_param,
	_obj_none,
}							t_obj_type;

typedef struct s_int_color
{
	int						a;
	int						r;
	int						v;
	int						b;
}							t_int_color;

// INIT
int							init_mlx(t_mlx_data *mlx);
void						init(t_global_data *g_data, t_parsing_data *p_data,
								char *av_zero);
void						init_viewport(t_viewport *viewport, int fov);

// PARSING
void						parser(int ac, char *av[], t_global_data *g_data,
								t_parsing_data *p_data);
void						check_args(int ac, char **av, char *prog_name);
int							open_map(char *filename, char *progname);
int							parse_pos(char *str, t_vect3 *pos,
								char normalized);
int							parse_raw_color(char *str, int *color);
int							parse_float(char *str, float *value);
t_color						parse_color(int color);
void						lst_map_to_array(t_parsing_data *p_data,
								t_world_data *world);
void						parse_object(t_parsing_data *p_data, char *obj_line,
								t_global_data *g_data);
void						parse_params(t_parsing_data *p_data, char *obj_line,
								t_global_data *g_data);

// RENDER
int							update_display(t_global_data *data);
int							get_color(t_color p_color);
int							get_color_chars(unsigned char a, unsigned char r,
								unsigned char g, unsigned char b);
int 						shading(t_vect3 ray, t_vect3 cam_pos, float t,
								t_object object, t_world_data *world);
// int							color_sup(int color_a, int color_b);
t_vect3					project(t_vect3 pos, t_cam_data *cam_data);
// void						my_mlx_pixel_put(t_mlx_data *mlx, t_vect3 pos,
// 								int color);
void						update_cam_pos(t_interface *input, t_cam_data *cam, int elapsed, bool *moving);
void						rotate_cam(t_cam_data *cam, t_mlx_data *mlx, bool *moving);
void						trace_rays(t_world_data *world, t_mlx_data *mlx);
// t_vect3					vector_norm(t_vect3 a);
// t_vect3					vector_cross(t_vect3 a, t_vect3 b);
void						render_canva(t_vect3 start, t_vect3 end,
								t_world_data *world, t_mlx_data *mlx);
// int							get_prev_color(t_vect3 pos, t_mlx_data *mlx);
double    					sphere_collision(t_vect3 ray, t_object *object, t_vect3 cam_pos);

// INPUT
void						set_hooks(t_global_data *g_data);
void						move_cam(t_world_data *world, t_mlx_data *mlx, t_interface *key, int elapsed);
void						set_moving_vector(bool moving, t_vect3 move, int elapsed);
t_vect3					get_lasting(void);

// UTILS
int							ft_puterr(char *error);
int							ft_error(char *error, char *progname);
int							ft_maperror(char *error, char *progname);
int							ft_perror(char *optional_name, char *progname);
char						*get_progname(char *av_zero);
unsigned long				get_time(unsigned long start);
unsigned long				get_utime(unsigned long start);
void						free_node(void *node);
void						clean_exit(int exit_status, t_global_data *g_data,
								t_parsing_data *p_data);
int							win_close(t_global_data *g_data);
void						print_objects(t_parsing_data *p_data,
								t_world_data *world);
void						print_array(t_world_data *world);
int							check_args_count(char **args, unsigned int min,
								unsigned int max);
int							is_normalized(t_vect3 pos);
t_obj_type					get_obj_type(char *obj_line);

#endif