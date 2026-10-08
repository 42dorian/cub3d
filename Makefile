NAME = cub3d

SOURCE =	src/valid_map_checker.c \
			src/parsing_cub_file.c 

CFLAGS = -Wall -Wextra -Werror -g

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
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJECTS) $(GNL_OBJ)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT)  $(GNL_OBJ) -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	$(RM) $(GNL_OBJ)
	$(RM) $(OBJECTS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all
