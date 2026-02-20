CC = cc
CFLAGS += -Wall -Wextra -Werror -Wpedantic -O3
DFLAGS += -g3 -D DEBUG=1 -O3

SRCS_DIR = srcs
SRCS = main.c\
		init.c\
		interface/inputs.c\
		interface/velocity.c\
		parsing/objects.c\
		parsing/open_map.c\
		parsing/params.c\
		parsing/parser.c\
		parsing/sub_parameters.c\
		rendering/colors.c\
		rendering/loop.c\
		rendering/move.c\
		rendering/object_collision.c\
		rendering/project.c\
		rendering/ray_tracer.c\
		rendering/shading.c\
		utils/clean_exit.c\
		utils/debug_obj_print.c\
		utils/debug_params_print.c\
		utils/debug_print.c\
		utils/errors.c\
		utils/parsing.c\
		utils/tools.c

OBJS_DIR = objs
OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))
DOBJS = $(patsubst %.c, $(OBJS_DIR)/%_DEBUG.o, $(SRCS))

DEPS = $(patsubst %.c, $(OBJS_DIR)/%.d, $(SRCS)) 

INCLUDES = includes

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = miniRT
DNAME = $(NAME)_debug

.PHONY = $(NAME) all clean fclean re debug

all : $(NAME)

debug : $(DNAME)

$(MLX) :
	make -C $(MLX_DIR)

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -I$(INCLUDES) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@
	
$(OBJS_DIR)/%_DEBUG.o : $(SRCS_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(DFLAGS) -MMD -I$(INCLUDES) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(INCLUDES) -I$(LIBFT_DIR) -I$(MLX_DIR) -L $(LIBFT_DIR) -L $(MLX_DIR) -lft -lmlx -L /usr/lib -lXext -lX11 -lm -lz

$(DNAME) : $(DOBJS) $(LIBFT) $(MLX)
	$(CC) $(DFLAGS) -o $(DNAME) $(DOBJS) -I$(INCLUDES) -I$(LIBFT_DIR) -I$(MLX_DIR) -L $(LIBFT_DIR) -L $(MLX_DIR) -lft -lmlx -L /usr/lib -lXext -lX11 -lm -lz

clean :
	$(RM) -rf $(OBJS) $(DEPS) $(DOBJS) $(DDEPS) $(OBJS_DIR)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)

fclean : clean
	$(RM) $(NAME) $(DNAME)
	make fclean -C $(LIBFT_DIR)

re : fclean all

-include $(DEPS)
