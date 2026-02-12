/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:47:31 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/12 13:21:16 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_args(int ac, char **av, char *prog_name)
{
	if (ac != 2)
	{
		ft_error("Invalid count of arguments", prog_name);
		exit(EXIT_FAILURE);
	}
	if (!ft_strnstr(av[1], ".rt", -1) || ft_strncmp(".rt", ft_strnstr(av[1],
				".rt", -1), 4))
		exit(ft_puterr("Only .rt format is supported\n"));
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
