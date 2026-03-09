/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:26:32 by lomartin          #+#    #+#             */
/*   Updated: 2026/03/09 15:27:18 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_READ_H
# define FILE_READ_H

int		peek(FILE *stream);
int		accept(FILE *stream, char c);
int		unexpected(FILE *stream, t_parsing_data *p_data, t_global_data *g_data);
int		expect(FILE *stream, char c, t_parsing_data *p_data,
			t_global_data *g_data);
int		accept_set(FILE *stream, char *set);
int		expect_set(FILE *stream, char *set, t_parsing_data *p_data,
			t_global_data *g_data);
void	skip_whitespaces(FILE *stream, int *line_count);
char	*get_token_name(char c);

#endif
