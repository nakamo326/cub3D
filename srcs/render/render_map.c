/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:27:35 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/14 17:39:33 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_map_floor(t_game *game, int x, int y)
{
	int i;
	int j;
	double scale;

	scale = TILE_SIZE * game->cub.map_scale;
	i = 0;
	while (i <= scale)
	{
		j = 0;
		while (j < scale)
		{
			my_mlx_pixel_put(&game->view, x * scale + i, y * scale + j, 0x012217);
			j++;
		}
		i++;
	}
}

void	render_map_wall(t_game *game, int x, int y)
{
	int		i;
	int		t;

	i = 0;
	t = TILE_SIZE * game->cub.map_scale;
	while (i <= TILE_SIZE * game->cub.map_scale)
	{
		if (game->cub.map[y][x - 1] == '1')
			my_mlx_pixel_put(&game->view, x * t, y * t + i, 0x00B007);
		if (game->cub.map[y - 1][x] == '1')
			my_mlx_pixel_put(&game->view, x * t + i, y * t, 0x00B007);
		if (game->cub.map[y][x + 1] == '1')
			my_mlx_pixel_put(&game->view, (x + 1) * t, y * t + i, 0x00B007);
		if (game->cub.map[y + 1][x] == '1')
			my_mlx_pixel_put(&game->view, x * t + i, (y + 1) * t, 0x00B007);
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
				render_map_floor(game, x, y);
				render_map_wall(game, x, y);
			}
			x++;
		}
		y++;
	}
	render_map_object(game);
}
