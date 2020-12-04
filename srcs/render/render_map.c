/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:27:35 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/04 13:30:16 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + ( y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	render_map_floor(t_data *map, t_cub cub, int x, int y)
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
		if (cub.map[y][x - 1] == '1')
			my_mlx_pixel_put(map, x * 20, y * 20 + i, 0x00B007);
		if (cub.map[y - 1][x] == '1')
			my_mlx_pixel_put(map, x * 20 + i, y * 20, 0x00B007);
		if (cub.map[y][x + 1] == '1')
			my_mlx_pixel_put(map, (x + 1) * 20, y * 20 + i, 0x00B007);
		if (cub.map[y + 1][x] == '1')
			my_mlx_pixel_put(map, x * 20 + i, (y + 1) * 20, 0x00B007);
		i++;
	}
}

void	render_map_wall(t_data *map, int x, int y)
{
	int i;

	i = 0;
	while (i < 20)
	{
		my_mlx_pixel_put(map, x * 20, y * 20 + i, 0x00B007);
		my_mlx_pixel_put(map, x * 20 + i, y * 20, 0x00B007);
		my_mlx_pixel_put(map, (x + 1) * 20, y * 20 + i, 0x00B007);
		my_mlx_pixel_put(map, x * 20 + i, (y + 1) * 20, 0x00B007);
		i++;
	}
}

//mapのcharに合わせてimgに描写、ひとまず線で枠書く？プレイヤーは上書きできるはず。
void	render_map(t_data *map, t_cub cub)
{
	int x;
	int y;

	y = 0;
	while (y < cub.map_maxrow)
	{
		x = 0;
		while (cub.map[y][x] != '\0')
		{
			if (cub.map[y][x] == '*' || cub.map[y][x] == '0')
				render_map_floor(map, cub, x, y);
			x++;
		}
		y++;
	}
	//y = 0;
	//while (y < cub.map_maxrow)
	//{
	//	x = 0;
	//	while (cub.map[y][x] != '\0')
	//	{
	//		if (cub.map[y][x] == '1')
	//			render_map_wall(map, x, y);
	//		x++;
	//	}
	//	y++;
	//}
}
