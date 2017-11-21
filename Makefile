# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhill <dhill@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/23 16:05:03 by dhill             #+#    #+#              #
#    Updated: 2017/11/16 01:01:41 by dhill            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FLAGS = -g -Wall -Wextra -Werror

FILES = main.c validate.c parse.c draw_line.c

SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(addprefix build/, ${FILES:.c=.o})

FRAMEWORKS = -framework OpenGL -framework AppKit

INC_MLX = -I includes/minilibx_macos
LNK_MLX = -L includes/minilibx_macos -lmlx #-l ignores lib part of name
MLX = $(INC_MLX) $(LNK_MLX)

INC_LFT = -I includes/libft
LNK_LFT = -L includes/libft -lft
LFT = $(INC_LFT) $(LNK_LFT)


.PHONY: all clean fclean re

all: $(NAME)

libft:
	make -C includes/libft re

minilibx:
	make -C includes/minilibx_macos re

$(NAME): libft minilibx $(OBJS)
	gcc $(FLAGS) $(MLX) $(LFT) -I includes $(FRAMEWORKS) $(OBJS) -o $(NAME)

build:
	mkdir build

build/%.o: srcs/%.c | build
	@echo "Building... $@"
	@gcc $(FLAGS) $(INC_MLX) $(INC_LFT) -I includes -c $< -o $@

clean:
	rm -rf build
	make -C includes/libft clean
	make -C includes/minilibx_macos clean

fclean: clean
	rm -f $(NAME)

re: fclean all
