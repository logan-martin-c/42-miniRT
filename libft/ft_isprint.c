/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:11:11 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:56:06 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief Test for printable character (including space)
** @param c int value to test
** @return Non-zero if printable, zero otherwise
*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
