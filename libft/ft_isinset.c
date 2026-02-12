/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:23:35 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:46:39 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief Check if character is in given set (string of chars)
** @param c character to check
** @param set null-terminated string containing characters of the set
** @return 1 if c is in set, 0 otherwise
*/
int	ft_isinset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
