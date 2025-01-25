# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 13:12:27 by hajmoham          #+#    #+#              #
#    Updated: 2025/01/25 14:11:14 by hajmoham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

LIBFT = ./libft/libft.a
PRINTF = ./Printf/libftprintf.a
MINILBX = ./mlx/libmlx.a

SRC = main.c check_map.c errors.c movement.c image.c get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c
OBJ := $(SRC:.c=.o)

MLXFLAGS = -Lmlx -framework OpenGL -framework AppKit

CFLAGS =  -g3 -Wall -Wextra -Werror -Iminilibx -Ilibft

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(PRINTF) $(MINILBX) $(OBJ)
	cc $(OBJ) $(LIBFT) $(PRINTF) $(MINILBX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	make -C ./libft
	
$(PRINTF):
	make -C ./Printf

$(MINILBX):
	make -C ./mlx

re: fclean all

clean:
	rm -rf $(OBJ)
	make clean -C ./libft
	make clean -C ./Printf
	make clean -C ./mlx

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft
	make fclean -C ./Printf

.PHONY: clean fclean all re