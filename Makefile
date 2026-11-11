NAME = cub3d

SOURCE =	src/valid_map_checker.c \
			src/parsing_cub_file.c \
			src/main.c \
			src/render.c \
			src/move.c \
			src/rotate.c \
			src/input.c \
			src/textures.c \
			src/clean_up_functions.c \
			src/error_messages.c \
			src/get_lengths.c \
			src/get_struct_values.c \
			src/input_validity.c \
			src/one_line_helpers.c \
			src/one_line_helpers_2.c \
			src/player_validity.c \
			src/set_directions.c 

CFLAGS = -Wall -Wextra -Werror -g
#we need to remove one of these in the future, either includes or mlx_flags
INCLUDES = -I./minilibx-linux -I/opt/X11/include -Iinclude/libft -Iinclude/get_next_line
MLX_FLAGS = -L./minilibx-linux -lmlx -L/opt/X11/lib -lXext -lX11 -lm
OBJECTS = $(SOURCE:.c=.o)


LIBFT_DIR = include/libft
GNL_DIR = include/get_next_line

GNL_SRC = include/get_next_line/get_next_line.c \
			include/get_next_line/get_next_line_utils.c
GNL_OBJ = $(GNL_SRC:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
RM = rm -f

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c src/cub3d.h include/libft/libft.h include/get_next_line/get_next_line.h
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJECTS) $(GNL_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT) $(GNL_OBJ) $(MLX_FLAGS) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	$(RM) $(GNL_OBJ)
	$(RM) $(OBJECTS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
