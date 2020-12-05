/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:18:39 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/05 12:44:35 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(t_img *map, t_pl player)
{
	//red dot with anti alias
	int x;
	int y;

	//player.x = player.x * 20 + 10;
	//player.y = player.y * 20 + 10;
	x = player.x;
	y = player.y;
	my_mlx_pixel_put(map, x * 20 + 10, y * 20 + 10, 0xFF0000);
	my_mlx_pixel_put(map, x * 20 + 11, y * 20 + 10, 0xFF0000);
	my_mlx_pixel_put(map, x * 20 +  9, y * 20 + 10, 0xFF0000);
	my_mlx_pixel_put(map, x * 20 + 10, y * 20 + 11, 0xFF0000);
	my_mlx_pixel_put(map, x * 20 + 10, y * 20 +  9, 0xFF0000);
	my_mlx_pixel_put(map, x * 20 +  9, y * 20 +  9, 0x80110B);
	my_mlx_pixel_put(map, x * 20 +  9, y * 20 + 11, 0x80110B);
	my_mlx_pixel_put(map, x * 20 + 11, y * 20 +  9, 0x80110B);
	my_mlx_pixel_put(map, x * 20 + 11, y * 20 + 11, 0x80110B);
}

void	render_map_object()
{}