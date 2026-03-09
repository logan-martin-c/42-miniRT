CC = cc
CFLAGS += -Wall -Wextra -Werror -Wpedantic -Ofast
DFLAGS += -g3 -D DEBUG=1 #-Ofast

LIBS += -lpthread -latomic

SRCS_DIR = srcs
SRCS = main.c\
		init.c\
		interface/gui.c\
		interface/inputs.c\
		interface/object_mover.c\
		interface/velocity.c\
		parsing/json_elements.c\
		parsing/json_parser.c\
		parsing/json_to_array.c\
		parsing/json_to_light.c\
		parsing/json_to_objects_1.c\
		parsing/json_to_objects_2.c\
		parsing/json_to_params.c\
		parsing/json_sub_parameters.c\
		parsing/map_to_array.c\
		parsing/objects.c\
		parsing/objects_2.c\
		parsing/open_map.c\
		parsing/params.c\
		parsing/parser.c\
		parsing/sub_parameters.c\
		parsing/texture.c\
		rendering/collisions.c\
		rendering/colors.c\
		rendering/loop.c\
		rendering/move.c\
		rendering/multithreading.c\
		rendering/ray_tracer.c\
		rendering/shading.c\
		rendering/texturing.c\
		rendering/normal.c\
		rendering/uv.c\
		utils/clean_exit.c\
		utils/debug_obj_print.c\
		utils/debug_params_print.c\
		utils/debug_print.c\
		utils/errors.c\
		utils/file_read.c\
		utils/file_read_set.c\
		utils/json.c\
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

bonus : $(NAME)

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
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(INCLUDES) -I$(LIBFT_DIR) -I$(MLX_DIR) -L $(LIBFT_DIR) -L $(MLX_DIR) -lft -lmlx -L /usr/lib -lXext -lX11 -lm -lz $(LIBS)

$(DNAME) : $(DOBJS) $(LIBFT) $(MLX)
	$(CC) $(DFLAGS) -o $(DNAME) $(DOBJS) -I$(INCLUDES) -I$(LIBFT_DIR) -I$(MLX_DIR) -L $(LIBFT_DIR) -L $(MLX_DIR) -lft -lmlx -L /usr/lib -lXext -lX11 -lm -lz $(LIBS)

clean :
	$(RM) -rf $(OBJS) $(DEPS) $(DOBJS) $(DDEPS) $(OBJS_DIR)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)

fclean : clean
	$(RM) $(NAME) $(DNAME)
	make fclean -C $(LIBFT_DIR)

re : fclean all

-include $(DEPS)
