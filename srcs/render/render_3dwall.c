/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3dwall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:33:10 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/10 16:29:50 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_view(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->cub.window_height)
	{
		j = 0;
		while (j < game->cub.window_width)
		{
			my_mlx_pixel_put(&game->view, j, i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	render_projected_wall(t_game *game)
{
	int i;
	int j;
	int wall_start;
	double ray_distance;
	double wall_height;
	double distance_plane;

	clear_view(game);
	i = 0;
	distance_plane = (game->cub.window_width / 2) / tan(FOV / 2);
	while (i < game->cub.window_width)
	{
		ray_distance = game->rays[i].distance;
		wall_height = (TILE_SIZE / ray_distance) * distance_plane;
		wall_start = (game->cub.window_height / 2) - (wall_height / 2);
		//just for test
		j = 0;
		while (j < wall_height)
		{
			my_mlx_pixel_put(&game->view, i, wall_start + j, 0x000000);
			j = j + 1;
		}
		i = i + 1;
	}
}