/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3dwall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:33:10 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/13 14:57:23 by ynakamot         ###   ########.fr       */
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
			my_mlx_pixel_put(&game->view, j, i, 0x444444);
			j++;
		}
		i++;
	}
}

void	render_projected_wall(t_game *game)
{
	int i;
	int j;
	double wall_start;
	double correct_distance;
	double wall_height;
	double distance_plane;

	clear_view(game);
	i = 0;
	distance_plane = (game->cub.window_width / 2) / tan(FOV / 2);
	while (i < game->cub.window_width)
	{
		if ((int)game->rays[i].distance > 0)
		{//remove after fixing move
			correct_distance = game->rays[i].distance
				* cos(game->rays[i].ray_angle - game->player.rotation_angle);
			wall_height = (TILE_SIZE / correct_distance) * distance_plane;
			wall_start = (game->cub.window_height / 2) - (wall_height / 2);
			j = 0;
			if (j + wall_start < 0)
				j -= wall_start;
			while (j < wall_height && wall_start + j < game->cub.window_height)
			{
				my_mlx_pixel_put(&game->view, i, wall_start + j, 0xffffff);
				j++;
			}
		}
		i = i + 1;
	}
}