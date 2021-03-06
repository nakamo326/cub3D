/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_map_scale.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 21:27:02 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/18 13:12:55 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_mapscale(t_game *game)
{
	int	map_width;
	int	map_height;

	map_width = game->cub.map_maxcol * TILE_SIZE * game->cub.map_scale;
	while (map_width * 3 >= game->cub.window_width)
	{
		game->cub.map_scale -= 0.1;
		map_width = game->cub.map_maxcol * TILE_SIZE * game->cub.map_scale;
	}
	map_height = game->cub.map_maxrow * TILE_SIZE * game->cub.map_scale;
	while (map_height * 3 >= game->cub.window_height)
	{
		game->cub.map_scale -= 0.1;
		map_height = game->cub.map_maxrow * TILE_SIZE * game->cub.map_scale;
	}
	if (game->cub.map_scale < 0.1)
		game->cub.map_scale = -1;
}
