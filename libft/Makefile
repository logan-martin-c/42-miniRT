CC = gcc
CFLAGS += -Wall -Wextra -Werror -O3

SRCS = ft_abs_bonus.c\
		ft_atof.c\
		ft_atod.c\
		ft_atoi.c\
		ft_atoi_base.c\
		ft_atol.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_free_strs.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isfloat.c\
		ft_isinset.c\
		ft_isprint.c\
		ft_isspace_bonus.c\
		ft_isvalidbase_bonus.c\
		ft_itoa.c\
		ft_lstadd_back_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstdelone_fr.c\
		ft_lstiter_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstmap_bonus.c\
		ft_lstnew_bonus.c\
		ft_lstsize_bonus.c\
		ft_max.c\
		ft_max_bonus.c\
		ft_memccpy_bonus.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_memset_int.c\
		ft_min.c\
		ft_min_bonus.c\
		ft_nblen_base_bonus.c\
		ft_nblen_base_ul_bonus.c\
		ft_nblen_bonus.c\
		ft_pow_bonus.c\
		ft_printf.c\
		ft_print_memory.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_base_fd_bonus.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_realloc.c\
		ft_split.c\
		ft_strchr.c\
		ft_strclen.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strcmp.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\
		printf_utils/nblens.c\
		printf_utils/padding.c\
		printf_utils/parse_flags.c\
		printf_utils/putnbrs.c\
		printf_utils/router.c\
		get_next_line.c\
		get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

INCLUDES = .
NAME = libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) rcs $(NAME) $(OBJS)

%.o : %.c
	$(CC) -g $(CFLAGS) -I$(INCLUDES) -c $< -o $@

fclean : clean
	$(RM) -rf $(NAME)

clean :
	$(RM) -rf $(OBJS)

re : fclean all

.PHONY: all clean fclean re bonus
