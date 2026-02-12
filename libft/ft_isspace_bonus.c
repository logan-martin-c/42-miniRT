/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 11:23:27 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 13:08:44 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief Test for whitespace characters (space, tab, newline, etc.)
** @param c int value to test
** @return Non-zero if whitespace, zero otherwise
*/
int	ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}
