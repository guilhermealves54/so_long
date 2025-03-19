# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 15:19:12 by gribeiro          #+#    #+#              #
#    Updated: 2025/03/19 15:50:08 by gribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = so_long

# Source files and object files
SRC = src/check_wayout.c src/create_map.c src/draw_map.c src/freemem.c src/ft_calloc.c src/ft_strdup.c src/ft_strjoin.c src/ft_strlen.c src/ft_strncmp.c src/keys.c src/movement.c src/so_long.c src/valid_map.c src/chk_assets.c
OBJS = $(SRC:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

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
	fi
	@if [ ! -f "$(MLX_DIR)/libmlx.a" ]; then \
		make -C $(MLX_DIR); \
	fi

ft_printf:
	@if [ ! -d "$(FT_PRINTF_DIR)" ]; then \
		git clone git@github.com:guilhermealves54/ft_printf.git $(FT_PRINTF_DIR); \
	fi
	make -C $(FT_PRINTF_DIR)

clean:
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean

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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./so_long maps/01.ber
