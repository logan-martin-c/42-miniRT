/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:15:30 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 12:49:53 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Apply function f to each character of s passing its index
** @param s String to iterate (modifies in place)
** @param f Function taking index and pointer to char
** @return void
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		f(i, s + i);
}
