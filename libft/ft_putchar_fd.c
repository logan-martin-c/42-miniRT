/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:11:52 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 12:51:23 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief Write character c to file descriptor fd
** @param c Character to write
** @param fd File descriptor
** @return void
*/
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
