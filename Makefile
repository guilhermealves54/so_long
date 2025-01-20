SRC	=	$(addprefix src/, ft_strlen.c ft_strncmp.c so_long.c ft_strdup.c ft_strjoin.c)
OBJS	=	$(SRCS:.c=.o)

CC = cc
#CFLAGS = -Wall -Wextra -Werror

$(NAME):
	$(OBJS)
	ar rcs ${NAME} ${OBJS}

test:
	cc $(SRC) $(CFLAGS) -o so_long.out
	./so_long.out maps/01.ber