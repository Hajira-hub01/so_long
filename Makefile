# Executable Name
NAME = so_long

# Compiler
CC = cc

# Compiler Flags
CFLAGS = -Wall -Wextra -Werror -g3

# Directories
LIBFT_DIR = ./libft
GET_NEXT_LINE_DIR = ./get_next_line
MLX_DIR = ./mlx/
PRINTF_DIR = ./ft_printf

# Libraries
LIBFT_LIB = $(LIBFT_DIR)/libft.a
GET_NEXT_LINE_LIB = $(GET_NEXT_LINE_DIR)/get_next_line.a
MLX_LIB = $(MLX_DIR)/libmlx.a
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

# Source files
SRCS = main.c check_map.c map.c path.c game.c movements.c parse.c read_layout.c find_player.c

# Object files
OBJS =	$(SRCS:.c=.o)
		



# Build Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(GET_NEXT_LINE_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(PRINTF_DIR)
	$(CC) $(OBJS) $(LIBFT_LIB) $(GET_NEXT_LINE_LIB) $(MLX_LIB) $(PRINTF_LIB) -o $(NAME) -Lmlx -lmlx -framework OpenGL -framework AppKit
# $(CC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
# $(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(GET_NEXT_LINE_LIB) $(MLX_LIB) -o $(NAME)


%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
# Clean Rules
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GET_NEXT_LINE_DIR) clean
# $(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean


fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GET_NEXT_LINE_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean

	# Assuming there's an fclean rule in the mlx directory Makefile
# $(MAKE) -C $(MLX_DIR) fclean

re: fclean all