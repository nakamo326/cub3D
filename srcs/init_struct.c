/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:43:32 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/06 14:19:11 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_flags(t_game *game)
{
	game->cub.win_f = false;
	game->cub.no_path_f = false;
	game->cub.so_path_f = false;
	game->cub.we_path_f = false;
	game->cub.ea_path_f = false;
	game->cub.sp_path_f = false;
	game->cub.f_color_f = false;
	game->cub.c_color_f = false;
}

void	init_player(t_game *game)
{
	game->player.x = 0;
	game->player.y = 0;
	game->player.spawn_direction = '\0';//error case
	game->player.turn_direction = 0;//-1 if left, 1 if right
	game->player.walk_direction = 0;//-1 if back, 1 if front
	game->player.sidewalk_direction = 0;//1 if left, -1 if right
	game->player.rotation_angle = 0;
	game->player.move_speed = 1.0;
	game->player.rotation_speed = 1 * PI / 180;
}

void	init_cub(t_game *game)
{
	game->cub.window_width = 640;
	game->cub.window_height= 480;
	game->cub.no_path = NULL;
	game->cub.so_path = NULL;
	game->cub.we_path = NULL;
	game->cub.ea_path = NULL;
	game->cub.sp_path = NULL;
	game->cub.f_color[0] = 0xFF;
	game->cub.f_color[1] = 0xFF;
	game->cub.f_color[2] = 0xFF;
	game->cub.c_color[0] = 0x11;
	game->cub.c_color[1] = 0x11;
	game->cub.c_color[2] = 0x11;
	game->cub.map[0] = NULL;
	game->cub.map_maxrow = 0;
	game->cub.map_maxcol = 0;
	game->cub.items = NULL;
}

void	init_val(t_game *game)
{
	init_cub(game);
	init_flags(game);
	init_player(game);
}
