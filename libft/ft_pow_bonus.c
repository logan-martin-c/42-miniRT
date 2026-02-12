/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:11:47 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:46:55 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief Compute base raised to exponent (integer power)
** @param base integer base
** @param exp  non-negative integer exponent
** @return base^exp as an integer (behavior on overflow undefined)
*/
long	ft_pow(int n, int pow)
{
	long	ret;

	ret = n;
	while (--pow)
		ret *= n;
	return (ret);
}
