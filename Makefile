NAME = so_long

LIBFT = ./libft/libft.a

SRC = main.c check_map.c errors.c get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c freeing.c
OBJ := $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Ilibft
LDFLAGS = -g3

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	cc $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C ./libft

re: fclean all

clean:
	rm -rf $(OBJ)
	make clean -C ./libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft

.PHONY: clean fclean all re
