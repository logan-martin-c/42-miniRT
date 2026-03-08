#ifndef READ_FILE_H
#define READ_FILE_H

int     peek(FILE *stream);
int     accept(FILE *stream, char c);
int     unexpected(FILE *stream, t_parsing_data *p_data, t_global_data *g_data);
int     expect(FILE *stream, char c, t_parsing_data *p_data, t_global_data *g_data);
int     accept_set(FILE *stream, char *set);
int     expect_set(FILE *stream, char *set, t_parsing_data *p_data, t_global_data *g_data);
void    skip_whitespaces(FILE *stream, int *line_count);
char    *get_token_name(char c);

#endif
