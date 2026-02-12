/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:21:42 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/12 14:26:25 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "map.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920

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

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef struct s_mlx_data
{
	void			*mlx;
	void			*win;
	struct
	{
		void		*img;
		char		*addr;
		int			bits_per_pixel;
		int			line_length;
		int			endian;
	} s_img_data;
}					t_mlx_data;

typedef struct s_world_data
{
	t_object		*objs;
}					t_world_data;

typedef struct s_parsing_data
{
	int				map_fd;
	t_list			*obj_lst;
	int				obj_count;
	t_map_data		map_data;
}					t_parsing_data;

typedef struct s_interface
{
	bool			w;
	bool			a;
	bool			s;
	bool			d;
	bool			space;
	bool			ctrl;
}					t_interface;

typedef struct s_global_data
{
	char			*prog_name;
	t_mlx_data		mlx;
	t_interface		key;
	t_world_data	world;
}					t_global_data;

// INIT
int					init_mlx(t_mlx_data *mlx);

// PARSING
void				check_args(int ac, char **av, char *prog_name);
int					open_map(char *filename, char *progname);
int					parse_map(int map_fd, t_global_data *g_data,
						t_parsing_data *p_data);
int					parse_pos(char *str, t_pos_xyz *pos);
int					parse_raw_color(char *str, int *color);
t_color				parse_color(int color);
void				lst_map_to_array(t_parsing_data *p_data,
						t_world_data *world);

// RENDER
int					update_display(t_global_data *data);
int					get_color_chars(char a, char r, char v, char b);

// INPUT
void				set_hooks(t_global_data *g_data);

// UTILS
int					ft_puterr(char *error);
int					ft_error(char *error, char *progname);
int					ft_maperror(char *error, char *progname);
int					ft_perror(char *optional_name, char *progname);
char				*get_progname(char *av_zero);
unsigned long		get_time(unsigned long start);
void				free_node(void *node);
void				clean_exit(int exit_status, t_global_data *g_data,
						t_parsing_data *p_data);
int					win_close(t_global_data *g_data);
void				print_nodes(t_parsing_data *p_data);

#endif