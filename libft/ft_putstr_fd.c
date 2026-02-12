/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:14:56 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 12:55:06 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Write string s to file descriptor fd (no newline)
** @param s Null-terminated string to write
** @param fd File descriptor
** @return void
*/
void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}
