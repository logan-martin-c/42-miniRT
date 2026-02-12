/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:40:38 by lomartin          #+#    #+#             */
/*   Updated: 2026/02/11 17:50:43 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countstrrchr(const char *s, char c)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && (!*(s + 1) || *(s + 1) == c))
			count++;
		s++;
	}
	return (count);
}

static int	ft_countstrrchr_charset(const char *s, char *charset)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (!ft_isinset(*s, charset) && (!*(s + 1) || ft_isinset(*(s + 1),
					charset)))
			count++;
		s++;
	}
	return (count);
}

char	**ft_split_charset(const char *s, char *charset)
{
	char			**dest;
	t_split_data	data;

	data.i = -1;
	data.n = ft_countstrrchr_charset(s, charset);
	dest = malloc((data.n + 1) * sizeof(char *));
	if (!s || !dest)
		return (NULL);
	while (++data.i < data.n)
	{
		while (ft_isinset(*s, charset))
			s++;
		data.len = ft_strcharsetlen(s, charset);
		dest[data.i] = ft_substr(s, 0, data.len);
		if (!dest[data.i])
		{
			while (--data.i > -1)
				free(dest[data.i]);
			free(dest);
			return (NULL);
		}
		s += data.len + 1;
	}
	dest[data.i] = NULL;
	return (dest);
}

/*
** @brief Split string s into an array of strings using delimiter c
** @param s Source string
** @param c Delimiter character
** @return Newly allocated NULL-terminated array of strings or NULL on failure
*/
char	**ft_split(const char *s, char c)
{
	char			**dest;
	t_split_data	data;

	data.i = -1;
	data.n = ft_countstrrchr(s, c);
	dest = malloc((data.n + 1) * sizeof(char *));
	if (!s || !dest)
		return (NULL);
	while (++data.i < data.n)
	{
		while (*s == c)
			s++;
		data.len = ft_strclen(s, c);
		dest[data.i] = ft_substr(s, 0, data.len);
		if (!dest[data.i])
		{
			while (--data.i > -1)
				free(dest[data.i]);
			free(dest);
			return (NULL);
		}
		s += data.len + 1;
	}
	dest[data.i] = NULL;
	return (dest);
}
