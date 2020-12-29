/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3dwall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:33:10 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/29 21:32:18 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_view(t_cub cub, t_img *view)
{
	int i;
	int j;

	i = 0;
	while (i < cub.window_height / 2)
	{
		j = 0;
		while (j < cub.window_width)
		{
			my_mlx_pixel_put(view, j, i, cub.c_color);
			j++;
		}
		i++;
	}
	while (i < cub.window_height)
	{
		j = 0;
		while (j < cub.window_width)
		{
			my_mlx_pixel_put(view, j, i, cub.f_color);
			j++;
		}
		i++;
	}
}

void	render_wall_strip(double distance_plane, int i, t_game *game)
{
	double	correct_distance;
	double	wall_height;
	int		wall_start;
	int		j;
	int		color;
	double	x_ratio;
	double	y_ratio;

	correct_distance = game->rays[i].distance
	* cos(game->rays[i].ray_angle - game->player.rotation_angle);
	wall_height = (TILE_SIZE / correct_distance) * distance_plane;
	wall_start = round((game->cub.window_height / 2) - (wall_height / 2));
	if (game->rays[i].vwall_hit)
		x_ratio = 1 - fmod(game->rays[i].vwall_y, TILE_SIZE) / TILE_SIZE;
	else
		x_ratio = 1 - fmod(game->rays[i].hwall_x, TILE_SIZE) / TILE_SIZE;
	j = wall_start > 0 ? wall_start : 0;
	while (j < game->cub.window_height && j < wall_height + wall_start)
	{
		y_ratio = (j - wall_start) / wall_height;
		color = get_wall_texture(game, i, x_ratio, y_ratio);
		my_mlx_pixel_put(&game->view, i, j, color);
		j++;
	}


}

void	render_projected_wall(t_game *game)
{
	int		i;
	double	distance_plane;

	//delete after coding ceil and floor projection
	clear_view(game->cub, &game->view);
	render_floor(game);

	i = 0;
	distance_plane = (game->cub.window_width / 2) / tan(FOV / 2);
	while (i < game->cub.window_width)
	{
		render_wall_strip(distance_plane, i, game);
		i = i + 1;
	}
}
