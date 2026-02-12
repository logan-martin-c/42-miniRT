/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:56:16 by lomartin          #+#    #+#             */
/*   Updated: 2025/11/23 11:46:59 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief Locate first occurrence of character c in string s
** @param s Null-terminated string to search
** @param c Character to find (interpreted as unsigned char)
** @return Pointer to first occurrence or NULL if not found
*/
char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str);
	return (0);
}
