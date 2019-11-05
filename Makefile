# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobin-h <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/09 19:52:27 by jrobin-h          #+#    #+#              #
#    Updated: 2019/09/21 15:40:48 by jrobin-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3

ifeq ($(shell uname), Linux)
CFLAGS += -Wno-unused-result
endif

SRCS_DIR = srcs/
BUILD_DIR = build/
INCL_DIR = includes/
INCL_INT_DIR = includes_internal/
INCL_LIB_DIR = libft/includes/

MAIN_SRCS = main.c \
			error.c

INPUT_SRCS = read_input/add_links.c \
read_input/build_graph.c \
read_input/check_line.c \
read_input/misc.c \
read_input/new_room.c \
read_input/read_input.c \
read_input/read_lines.c

SOLUTION_SRCS = find_solution/build_update_residual_graph.c \
find_solution/build_paths.c \
find_solution/find_solution.c \
find_solution/dijkstra.c \
find_solution/get_turns.c \
find_solution/update_flow.c \
find_solution/update_distances.c \
find_solution/del_paths.c \
find_solution/copy_nodes.c \
find_solution/is_edge_to.c

OUTPUT_SRCS = output/del_ants.c \
output/build_ants.c \
output/output.c

MAIN_OBJS = $(MAIN_SRCS:.c=.o)
INPUT_OBJS = $(INPUT_SRCS:.c=.o)
SOLUTION_OBJS = $(SOLUTION_SRCS:.c=.o)
OUTPUT_OBJS = $(OUTPUT_SRCS:.c=.o)

vpath %.o $(BUILD_DIR)
vpath %.c $(SRCS_DIR)

all: check_build_dir build_lib build_vizu $(NAME)

$(NAME): 	$(MAIN_OBJS) \
			$(INPUT_OBJS) \
			$(SOLUTION_OBJS) \
			$(OUTPUT_OBJS) \
			libft/libft.a
	$(CC) \
	$(addprefix $(BUILD_DIR), $(MAIN_OBJS)) \
	$(addprefix $(BUILD_DIR), $(INPUT_OBJS)) \
	$(addprefix $(BUILD_DIR), $(SOLUTION_OBJS)) \
	$(addprefix $(BUILD_DIR), $(OUTPUT_OBJS)) \
	-L./libft -lft \
	-o $(NAME)

$(MAIN_OBJS): %.o : %.c \
		$(addprefix $(INCL_DIR), args.h) \
		$(addprefix $(INCL_DIR), error.h) \
		$(addprefix $(INCL_DIR), find_solution.h) \
		$(addprefix $(INCL_DIR), graph_customisation.h) \
		$(addprefix $(INCL_DIR), output.h) \
		$(addprefix $(INCL_DIR), read_input.h) \
		$(addprefix $(INCL_DIR), solution.h)
	$(CC) $(CFLAGS) \
	-I $(INCL_DIR) -I $(INCL_LIB_DIR) \
	-c $< -o $(BUILD_DIR)$@

$(INPUT_OBJS): %.o : %.c \
		$(addprefix $(INCL_DIR), args.h) \
		$(addprefix $(INCL_DIR), error.h) \
		$(addprefix $(INCL_DIR), graph_customisation.h) \
		$(addprefix $(INCL_DIR), read_input.h) \
		$(addprefix $(INCL_INT_DIR), read_input_internal.h) 
	$(CC) $(CFLAGS) \
	-I $(INCL_DIR) -I $(INCL_LIB_DIR) \
	-I $(INCL_INT_DIR) \
	-c $< -o $(BUILD_DIR)$@

$(SOLUTION_OBJS): %.o : %.c \
		$(addprefix $(INCL_DIR), find_solution.h) \
		$(addprefix $(INCL_DIR), solution.h) \
		$(addprefix $(INCL_INT_DIR), find_solution_internal.h) 
	$(CC) $(CFLAGS) \
	-I $(INCL_DIR) -I $(INCL_LIB_DIR) \
	-I $(INCL_INT_DIR) \
	-c $< -o $(BUILD_DIR)$@

$(OUTPUT_OBJS): %.o : %.c \
		$(addprefix $(INCL_DIR), output.h) \
		$(addprefix $(INCL_DIR), solution.h) \
		$(addprefix $(INCL_INT_DIR), output_internal.h) 
	$(CC) $(CFLAGS) \
	-I $(INCL_DIR) -I $(INCL_LIB_DIR) \
	-I $(INCL_INT_DIR) \
	-c $< -o $(BUILD_DIR)$@

.PHONY: check_build_dir
check_build_dir:
	@if [ ! -d $(BUILD_DIR) ] ; then \
	mkdir $(BUILD_DIR); \
	mkdir $(BUILD_DIR)find_solution; \
	mkdir $(BUILD_DIR)read_input; \
	mkdir $(BUILD_DIR)output; \
	fi

.PHONY: build_lib
build_lib:
	make -C ./libft

.PHONY: build_vizu
build_vizu:
	make -C ./vizu

./libft/libft.a: build_lib

FCLEANING = 0

.PHONY: update_fcleaning
update_fcleaning:
	$(eval FCLEANING = 1)

clean:
	rm -f $(addprefix $(BUILD_DIR), $(MAIN_OBJS)) \
		$(addprefix $(BUILD_DIR), $(INPUT_OBJS)) \
		$(addprefix $(BUILD_DIR), $(SOLUTION_OBJS)) \
		$(addprefix $(BUILD_DIR), $(OUTPUT_OBJS))
	@if [ $(FCLEANING) -eq 0 ] ; then \
	make -C ./libft clean; \
	make -C ./vizu clean; \
	fi

fclean: update_fcleaning clean
	rm -f $(NAME)
	make -C ./libft fclean
	make -C ./vizu fclean

re: fclean all

.PHONY: all re clean fclean
