/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:20:20 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 12:00:22 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief Test for digit character ('0'..'9')
** @param c int value to test
** @return Non-zero if digit, zero otherwise
*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
