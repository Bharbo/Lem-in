# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/21 15:41:08 by jrobin-h          #+#    #+#              #
#    Updated: 2019/09/21 16:06:20 by jrobin-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = vizu

SRCS = build_graph.c \
	build_line.c \
	determine_get_line_type.c \
	draw_line.c \
	ft_abs.c \
	get_next_move.c \
	main.c \
	memclean.c \
	output_step.c \
	read_input.c \
	read_lines.c \
	scale_coordinates.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: build_lib $(NAME)

$(NAME): ../libft/libft.a $(OBJS)
	$(CC) -lncurses -L../libft -lft $(OBJS) -o $(NAME)

$(OBJS): %.o : %.c vizu.h
	$(CC) $(CFLAGS) -I. -I../libft/includes -c $<

.PHONY: build_lib
build_lib:
ifeq ($(MAKELEVEL), 0)
	make -C ../libft
endif

../libft/libft.a: build_lib

clean:
	rm -f $(OBJS)
ifeq ($(MAKELEVEL), 0)
	make -C ../libft clean
endif

fclean: clean
	rm -f $(NAME)
ifeq ($(MAKEFILE), 0)
	make -C ../libft fclean
endif

re: fclean all

.PHONY: all clean fclean re
