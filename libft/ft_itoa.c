/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 20:38:31 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/11 17:12:16 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @brief Convert integer to a string and writes on the given pointer
** @param n Integer to convert
** @param nb allocated pointer
** @return Newly allocated string representing n or NULL on failure
*/
char	*ft_itoa_pure(int n, char *nb)
{
	size_t	len;
	int		neg;

	if (!nb)
		return (NULL);
	len = 1;
	neg = 0;
	while ((long)n / ft_pow(10, len))
		len++;
	if (n < 0)
		neg++;
	if (neg)
		nb[0] = '-';
	nb[neg + len--] = '\0';
	while (len)
	{
		nb[neg + len--] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	nb[neg + len--] = ft_abs(n % 10) + '0';
	return (nb);
}

/*
** @brief Convert integer to newly allocated string
** @param n Integer to convert
** @return Newly allocated string representing n or NULL on failure
*/
char	*ft_itoa(int n)
{
	char	*nb;
	size_t	len;
	int		neg;

	len = 1;
	neg = 0;
	while ((long)n / ft_pow(10, len))
		len++;
	if (n < 0)
		neg++;
	nb = malloc(len + neg + 1);
	if (!nb)
		return (NULL);
	nb = ft_itoa_pure(n, nb);
	return (nb);
}
