/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:27:35 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/14 22:25:23 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_map_floor(t_game *game, int x, int y)
{
	int		i;
	int		j;
	int		tile_x;
	int		tile_y;
	double	scale;

	scale = game->cub.map_scale;
	i = 0;
	tile_x = x * TILE_SIZE;
	tile_y = y * TILE_SIZE;
	while (i <= TILE_SIZE * scale)
	{
		j = 0;
		while (j < TILE_SIZE * scale)
		{
			my_mlx_pixel_put(&game->view,
				tile_x * scale + i, tile_y * scale + j, 0x012217);
			j++;
		}
		i++;
	}
}

void	render_map_wall(t_game *game, int x, int y)
{
	int		i;
	double	s;
	int		tile_x;
	int		tile_y;

	i = 0;
	s = game->cub.map_scale;
	tile_x = x * TILE_SIZE;
	tile_y = y * TILE_SIZE;
	while (i <= TILE_SIZE * s)
	{
		if (game->cub.map[y][x - 1] == '1')
			my_mlx_pixel_put(&game->view, tile_x * s, tile_y * s + i, 0x00B007);
		if (game->cub.map[y - 1][x] == '1')
			my_mlx_pixel_put(&game->view, tile_x * s + i, tile_y * s, 0x00B007);
		if (game->cub.map[y][x + 1] == '1')
			my_mlx_pixel_put(&game->view,
				(tile_x + TILE_SIZE) * s, tile_y * s + i, 0x00B007);
		if (game->cub.map[y + 1][x] == '1')
			my_mlx_pixel_put(&game->view,
				tile_x * s + i, (tile_y + TILE_SIZE) * s, 0x00B007);
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int	x;
	int	y;

	if (game->map_toggle == false)
		return ;
	y = 0;
	while (y < game->cub.map_maxrow)
	{
		x = 0;
		while (game->cub.map[y][x] != '\0')
		{
			if (game->cub.map[y][x] == '*' || game->cub.map[y][x] == '0')
			{
				render_map_floor(game, x, y);
				render_map_wall(game, x, y);
			}
			x++;
		}
		y++;
	}
	render_map_object(game);
}
