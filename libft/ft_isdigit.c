/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:20:20 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/14 15:27:25 by lomartin         ###   ########.fr       */
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

/*
** @brief Test if a string is only digit composed
** @param str string to test
** @return Non-zero if digit, zero otherwise
*/
int	ft_isdigit_str(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*(str++)))
			return (0);
	}
	return (1);
}
