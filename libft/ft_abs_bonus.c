/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:10:19 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 13:19:57 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief Returns the absolute value of an integer
** @param n Long int to process
** @return Absulute value of n
*/
long	ft_abs(long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

float	ft_abs_float(float n)
{
	if (n < 0.0)
		return (-n);
	return (n);
}

double	ft_abs_double(double n)
{
	if (n < 0.0)
		return (-n);
	return (n);
}
