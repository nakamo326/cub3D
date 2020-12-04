/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:43:32 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/04 16:50:30 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_flags(t_cub *cub)
{
	cub->win_f = false;
	cub->no_path_f = false;
	cub->so_path_f = false;
	cub->we_path_f = false;
	cub->ea_path_f = false;
	cub->sp_path_f = false;
	cub->f_color_f = false;
	cub->c_color_f = false;
}

void	init_player(t_cub *cub)
{
	cub->player.x = 0;
	cub->player.y = 0;
	cub->player.spawn_direction = '\0';//error case
	cub->player.turn_direction = 0;//-1 if left, 1 if right
	cub->player.walk_direction = 0;//-1 if back, 1 if front
	cub->player.rotation_angle = PI / 2;
	cub->player.move_speed = 3.0;
	cub->player.rotation_speed = 3 * PI / 180;
}

void	init_cub(t_cub *cub)
{
	cub->window_width = 640;
	cub->window_height= 480;
	cub->no_path = NULL;
	cub->so_path = NULL;
	cub->we_path = NULL;
	cub->ea_path = NULL;
	cub->sp_path = NULL;
	cub->f_color[0] = 0xFF;
	cub->f_color[1] = 0xFF;
	cub->f_color[2] = 0xFF;
	cub->c_color[0] = 0x11;
	cub->c_color[1] = 0x11;
	cub->c_color[2] = 0x11;
	cub->map[0] = NULL;
	cub->map_maxrow = 0;
	cub->map_maxcol = 0;
	init_flags(cub);
	init_player(cub);
}
