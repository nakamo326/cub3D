/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:27:35 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/05 11:16:08 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + ( y * data->len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	render_map_floor(t_img *map, t_cub *cub, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i <= 20)
	{
		j = 0;
		while (j < 20)
		{
			my_mlx_pixel_put(map, x * 20 + i, y * 20 + j, 0x012217);
			j++;
		}
		i++;
	}
	i = 0;
	while (i <= 20)
	{
		if (cub->map[y][x - 1] == '1')
			my_mlx_pixel_put(map, x * 20, y * 20 + i, 0x00B007);
		if (cub->map[y - 1][x] == '1')
			my_mlx_pixel_put(map, x * 20 + i, y * 20, 0x00B007);
		if (cub->map[y][x + 1] == '1')
			my_mlx_pixel_put(map, (x + 1) * 20, y * 20 + i, 0x00B007);
		if (cub->map[y + 1][x] == '1')
			my_mlx_pixel_put(map, x * 20 + i, (y + 1) * 20, 0x00B007);
		i++;
	}
}

void	render_player(t_img *map, t_pl player)
{
	//red dot with anti alias
	int x;
	int y;

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

void	render_map(t_img *map, t_cub *cub, t_pl player)
{
	int x;
	int y;

	y = 0;
	while (y < cub->map_maxrow)
	{
		x = 0;
		while (cub->map[y][x] != '\0')
		{
			if (cub->map[y][x] == '*' || cub->map[y][x] == '0')
				render_map_floor(map, cub, x, y);
			x++;
		}
		y++;
	}
	render_player(map, player);
}
