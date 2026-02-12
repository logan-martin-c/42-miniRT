/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:24:04 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/11 19:12:37 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char *av[])
{
	t_global_data	g_data;
	t_parsing_data	p_data;

	ft_bzero(&g_data, sizeof(t_global_data));
	g_data.prog_name = get_progname(av[0]);
	check_args(ac, av, g_data.prog_name);
	p_data.map_fd = open_map(av[1], g_data.prog_name);
	parse_map(p_data.map_fd, &g_data);
	close(p_data.map_fd);
	p_data.map_fd = -1;
	if (init_mlx(&g_data.mlx))
	{
		ft_perror("mlx", g_data.prog_name);
		clean_exit(EXIT_FAILURE, &g_data, &p_data);
	}
	set_hooks(&g_data);
	// mlx_do_key_autorepeatoff(vars.mlx);
	mlx_loop(g_data.mlx.mlx);
}
