/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:27:35 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/05 12:55:14 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + ( y * data->len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	render_map_floor(t_img *map, int x, int y)
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
}

void	render_map_wall(t_game *game, int x, int y)
{
	int i;

	i = 0;
	while (i <= 20)
	{
		if (game->cub.map[y][x - 1] == '1')
			my_mlx_pixel_put(&game->map, x * 20, y * 20 + i, 0x00B007);
		if (game->cub.map[y - 1][x] == '1')
			my_mlx_pixel_put(&game->map, x * 20 + i, y * 20, 0x00B007);
		if (game->cub.map[y][x + 1] == '1')
			my_mlx_pixel_put(&game->map, (x + 1) * 20, y * 20 + i, 0x00B007);
		if (game->cub.map[y + 1][x] == '1')
			my_mlx_pixel_put(&game->map, x * 20 + i, (y + 1) * 20, 0x00B007);
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->cub.map_maxrow)
	{
		x = 0;
		while (game->cub.map[y][x] != '\0')
		{
			if (game->cub.map[y][x] == '*' || game->cub.map[y][x] == '0')
			{
				render_map_floor(&game->map, x, y);
				render_map_wall(game, x, y);
			}
			x++;
		}
		y++;
	}
	render_map_object(game);
}
