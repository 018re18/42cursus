NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinclude -Iminilibx-linux
MLX_DIR		= minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS		= src/main.c src/parser.c src/parser_elements.c src/parser_map.c \
			  src/file.c src/map.c src/raycast.c src/renderer.c src/player.c \
			  src/events.c src/cleanup.c src/utils.c src/string_utils.c \
			  src/textures.c
OBJS		= $(SRCS:src/%.c=obj/%.o)

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

obj/%.o: src/%.c include/cub3d.h
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj
	rm -rf $(MLX_DIR)/obj
	rm -f $(MLX_LIB) $(MLX_DIR)/libmlx_Linux.a $(MLX_DIR)/Makefile.gen
	rm -f $(MLX_DIR)/test/*.o $(MLX_DIR)/test/mlx-test
	rm -f $(MLX_DIR)/test/makefile.gen

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
