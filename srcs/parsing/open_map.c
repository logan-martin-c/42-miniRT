/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:47:31 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/08 22:40:25 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_args(int ac, char **av, char *prog_name, t_file_type *file_type)
{
	if (ac != 2)
	{
		ft_error("Invalid count of arguments", prog_name);
		exit(EXIT_FAILURE);
	}
	if (ft_strnstr(av[1], ".rt", -1) && !ft_strncmp(".rt", ft_strnstr(av[1],
				".rt", -1), 4))
		*file_type = _rt;
	else if (ft_strnstr(av[1], ".json", -1) && !ft_strncmp(".json",
			ft_strnstr(av[1], ".json", -1), 6))
		*file_type = _json;
	else
		exit(ft_puterr("Only .rt and .json format are supported\n"));
}

int	open_map(char *filename, char *progname)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_perror(filename, progname);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
