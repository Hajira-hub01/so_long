NAME = so_long

LIBFT = ./libft/libft.a
MINILBX = ./minilibx/libmlx.a

SRC = main.c check_map.c errors.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJ := $(SRC:.c=.o)

CFLAGS = -fsanitize=address -g3 -Wall -Wextra -Werror -Iminilibx -Ilibft
LDFLAGS = -fsanitize=address

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MINILBX) $(OBJ)
	cc $(OBJ) $(LIBFT) $(MINILBX) -Lminilibx -lmlx -framework OpenGL -framework AppKit $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C ./libft

$(MINILBX):
	make -C ./minilibx

re: fclean all

clean:
	rm -rf $(OBJ)
	make clean -C ./libft
	make clean -C ./minilibx

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft

.PHONY: clean fclean all re
