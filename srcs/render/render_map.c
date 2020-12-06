/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:27:35 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/06 10:06:05 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	clear_transparecy(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->cub.map_maxrow * TILE_SIZE)
	{
		x= 0;
		while (x < game->cub.map_maxcol * TILE_SIZE)
		{
			my_mlx_pixel_put(&game->map, x, y, 0xFF000000);
			x++;
		}
		y++;
	}

}

void	render_map_floor(t_img *map, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i <= TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(map, x * TILE_SIZE + i, y * TILE_SIZE + j, 0x012217);
			j++;
		}
		i++;
	}
}

void	render_map_wall(t_game *game, int x, int y)
{
	int i;

	i = 0;
	while (i <= TILE_SIZE)
	{
		if (game->cub.map[y][x - 1] == '1')
			my_mlx_pixel_put(&game->map, x * TILE_SIZE, y * TILE_SIZE + i, 0x00B007);
		if (game->cub.map[y - 1][x] == '1')
			my_mlx_pixel_put(&game->map, x * TILE_SIZE + i, y * TILE_SIZE, 0x00B007);
		if (game->cub.map[y][x + 1] == '1')
			my_mlx_pixel_put(&game->map, (x + 1) * TILE_SIZE, y * TILE_SIZE + i, 0x00B007);
		if (game->cub.map[y + 1][x] == '1')
			my_mlx_pixel_put(&game->map, x * TILE_SIZE + i, (y + 1) * TILE_SIZE, 0x00B007);
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int x;
	int y;

	y = 0;
	//need test this function
	clear_transparecy(game);
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
