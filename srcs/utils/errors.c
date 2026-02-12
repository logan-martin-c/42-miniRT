/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:43:44 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/11 12:42:50 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_puterr(char *error)
{
	ft_putstr_fd(error, 2);
	return (EXIT_FAILURE);
}

int	ft_error(char *error, char *progname)
{
	char *error_str = NULL;
	
	if (error)
		error_str = ft_strjoin_mult(4, progname, ": ", error, "\n");
	if (!error_str && progname)
	{
		perror(progname);
		return(EXIT_FAILURE);
	}
	if (!progname)
		return (EXIT_FAILURE);
	ft_putstr_fd(error_str, 2);
	free(error_str);
	return (EXIT_FAILURE);
}

int	ft_maperror(char *error, char *progname)
{
	char *error_str = NULL;
	
	if (error)
		error_str = ft_strjoin_mult(3, "Error\n", error, "\n");
	if (!error_str && progname)
	{
		perror(progname);
		return(EXIT_FAILURE);
	}
	if (!progname)
		return (EXIT_FAILURE);
	ft_putstr_fd(error_str, 2);
	free(error_str);
	return (EXIT_FAILURE);
}

int ft_perror(char *optional_name, char *progname)
{
	char *error_prefix = NULL;
	
	if (optional_name)
		error_prefix = ft_strjoin_mult(3, progname, ": ", optional_name);
	else
		error_prefix = progname;
	if (!error_prefix && progname)
	{
		perror(progname);
		return (EXIT_FAILURE);
	}
	if (!progname)
		return (EXIT_FAILURE);
	perror(error_prefix);
	free(error_prefix);
	return (EXIT_FAILURE);
}
