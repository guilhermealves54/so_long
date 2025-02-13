# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 15:19:12 by gribeiro          #+#    #+#              #
#    Updated: 2025/02/12 23:51:30 by gribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = so_long

# Source files and object files
SRC = $(addprefix src/, ft_strlen.c ft_strncmp.c so_long.c ft_strdup.c ft_strjoin.c ft_calloc.c check_wayout.c freemem.c create_map.c valid_map.c)
OBJS = $(SRC:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# ft_printf
FT_PRINTF_DIR = ./ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a
FT_PRINTF_INC = -I$(FT_PRINTF_DIR)

# MiniLibX configuration
MLX_DIR = ./minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBS = -L$(MLX_DIR) -lmlx -lm -lXext -lX11

# Rules
all: mlx ft_printf $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(FT_PRINTF_LIB) -o $(NAME)

mlx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
		make -C $(MLX_DIR); \
	fi

ft_printf:
	@if [ ! -d "$(FT_PRINTF_DIR)" ]; then \
		git clone git@github.com:guilhermealves54/ft_printf.git $(FT_PRINTF_DIR); \
		make -C $(FT_PRINTF_DIR); \
	fi

clean:
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@if [ -d "$(MLX_DIR)" ]; then \
		rm -rf $(MLX_DIR); \
	fi
	@if [ -d "$(FT_PRINTF_DIR)" ]; then \
		rm -rf $(FT_PRINTF_DIR); \
	fi
	@if [ -f "so_long" ]; then \
		rm so_long; \
	fi

re: fclean all

test: all
	./$(NAME) maps/01.ber

valgrind: all
	valgrind --track-origins=yes ./so_long maps/01.ber
