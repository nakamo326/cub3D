# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 09:09:02 by ynakamot          #+#    #+#              #
#    Updated: 2021/01/16 19:26:01 by ynakamot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
NAME = cub3D

SRCFILE =	get_next_line/get_next_line.c \
			srcs/main.c \
			srcs/arg_check.c \
			srcs/error_handle.c \
			srcs/init_struct.c \
			srcs/export_bmp.c \
			srcs/open_texture.c \
			srcs/sort_sprite.c \
			srcs/cal_shot.c \
			srcs/config/read_config.c \
			srcs/config/perse_params.c \
			srcs/config/perse_map.c \
			srcs/config/map_validation.c \
			srcs/config/store_object_info.c \
			srcs/config/check_params.c \
			srcs/config/adjust_map_scale.c \
			srcs/config/perse_utils.c \
			srcs/loop/loop.c \
			srcs/loop/hook.c \
			srcs/loop/move.c \
			srcs/loop/update_sprite.c \
			srcs/raycasting/cast_ray.c \
			srcs/raycasting/check_intersection.c \
			srcs/render/render_map.c \
			srcs/render/render_map_object.c \
			srcs/render/render_utils.c \
			srcs/render/render_line.c \
			srcs/render/render_wall_strip.c \
			srcs/render/render_wall_texture.c \
			srcs/render/render_floor.c \
			srcs/render/render_sprite.c \
			srcs/render/render_sprite_strip.c \
			srcs/render/choose_sprite_tex.c \
			srcs/render/render_sky.c \
			srcs/render/render_reticle.c \
			srcs/render/add_shadow.c \
			srcs/render/render_hitpoint.c


OBJDIR = ./obj
OBJECTS = $(SRCFILE:.c=.o)

all: $(NAME)

libft:
	$(MAKE) bonus -C ./libft

minilibx:
	$(MAKE) do_configure -C ./minilibx-linux

$(NAME): libft minilibx $(OBJECTS)
	gcc -g $(SRCFILE) -I./includes -L./libft -L./minilibx-linux -lft -lmlx -lXext -lX11 -lm -o cub3D

bonus: libft minilibx $(OBJECTS)
	gcc -g $(SRCFILE) -I./includes -L./libft -L./minilibx-linux -lft -lmlx -lXext -lX11 -lm -o cub3D -DBONUS_F=1

run: all
	./cub3D sample.cub

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ -I./includes

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./minilibx-linux
	$(RM) $(OBJECTS)

fclean:
	$(MAKE) fclean -C ./libft
	$(MAKE) clean -C ./minilibx-linux
	$(RM) $(OBJECTS) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft minilibx