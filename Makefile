# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 13:12:27 by hajmoham          #+#    #+#              #
#    Updated: 2025/01/06 12:45:27 by hajmoham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

LIBFT = ./libft/libft.a
MINILBX = ./mlx/libmlx.a

SRC = main.c check_map.c errors.c get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c
OBJ := $(SRC:.c=.o)

MLXFLAGS = -Lmlx -framework OpenGL -framework AppKit

CFLAGS =  -g3 -Wall -Wextra -Werror -Iminilibx -Ilibft

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MINILBX) $(OBJ)
	cc $(OBJ) $(LIBFT) $(MINILBX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	make -C ./libft

$(MINILBX):
	make -C ./mlx

re: fclean all

clean:
	rm -rf $(OBJ)
	make clean -C ./libft
	make clean -C ./mlx

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft

.PHONY: clean fclean all re