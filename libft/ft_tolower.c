/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:26:17 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:59:54 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief Convert uppercase letter to lowercase if applicable
** @param c int representing a character
** @return Lowercase equivalent or original value
*/
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
