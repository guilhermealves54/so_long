# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 15:19:12 by gribeiro          #+#    #+#              #
#    Updated: 2025/02/07 03:21:36 by gribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = so_long

# Source files and object files
SRC = $(addprefix src/, ft_strlen.c ft_strncmp.c so_long.c ft_strdup.c ft_strjoin.c ft_calloc.c check_wayout.c freemem.c create_map.c valid_map.c)
OBJS = $(SRC:.c=.o)

# Compiler and flags
CC = cc
#CFLAGS = -Wall -Wextra -Werror -g #apagar

# MiniLibX configuration
MLX_DIR = ./minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBS = -L$(MLX_DIR) -lmlx -lm -lXext -lX11

# Rules
all: mlx $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

mlx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME) maps/01.ber

valgrind: all
	valgrind --track-origins=yes ./so_long maps/01.ber