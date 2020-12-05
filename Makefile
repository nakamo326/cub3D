# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 09:09:02 by ynakamot          #+#    #+#              #
#    Updated: 2020/12/05 12:32:58 by ynakamot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
NAME = cub3D

SRCFILE =	get_next_line/get_next_line.c \
			srcs/testcode.c \
			srcs/config/init_config.c \
			srcs/config/perse_params.c \
			srcs/config/perse_map.c \
			srcs/main.c \
			srcs/init_struct.c \
			srcs/error_handle.c \
			srcs/render/render_map.c \
			srcs/render/render_map_object.c



OBJECTS = $(SRCFILE:.c=.o)

all: $(NAME)

libft:
	$(MAKE) bonus -C ./libft

$(NAME): libft $(OBJECTS)
	gcc -g $(SRCFILE) -I./includes -L./libft -lft -lmlx -lXext -lX11 -o cub3D

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ -I./includes

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJECTS)

fclean:
	$(MAKE) fclean -C ./libft
	$(RM) $(OBJECTS) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft