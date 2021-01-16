/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_strip.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:33:10 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/16 13:39:24 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_view(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->cub.window_height / 2)
	{
		j = 0;
		while (j < game->cub.window_width)
		{
			my_mlx_pixel_put(&game->view, j, i, game->cub.c_color);
			j++;
		}
		i++;
	}
	while (i < game->cub.window_height)
	{
		j = 0;
		while (j < game->cub.window_width)
		{
			my_mlx_pixel_put(&game->view, j, i, game->cub.f_color);
			j++;
		}
		i++;
	}
}

double	get_x_ratio(t_ray ray)
{
	double x_ratio;

	if (ray.facing_up && ray.hwall_hit)
		x_ratio = fmod(ray.hwall_x, TILE_SIZE) / TILE_SIZE;
	if (ray.facing_down && ray.hwall_hit)
		x_ratio = 1 - fmod(ray.hwall_x, TILE_SIZE) / TILE_SIZE;
	if (ray.facing_right && ray.vwall_hit)
		x_ratio = fmod(ray.vwall_y, TILE_SIZE) / TILE_SIZE;
	if (ray.facing_left && ray.vwall_hit)
		x_ratio = 1 - fmod(ray.vwall_y, TILE_SIZE) / TILE_SIZE;
	return (x_ratio);
}

void	render_wall_strip(int i, t_game *game)
{
	double	wall_height;
	int		wall_start;
	int		j;
	double	x_ratio;
	double	y_ratio;

	game->zbuffer[i] = game->rays[i].distance
	* cos(game->rays[i].ray_angle - game->player.rotation_angle);
	wall_height = (TILE_SIZE / game->zbuffer[i]) * game->dist_plane;
	wall_start = round((game->cub.window_height / 2) - (wall_height / 2));
	x_ratio = get_x_ratio(game->rays[i]);
	j = wall_start > 0 ? wall_start : 0;
	while (j < game->cub.window_height && j < wall_height + wall_start)
	{
		y_ratio = (j - wall_start) / wall_height;
		my_mlx_pixel_put(&game->view, i, j,
			get_wall_texture(game, i, x_ratio, y_ratio));
		j++;
	}
	if (BONUS_F == 1)
		render_floor(game, i, j);
}

void	render_projected_wall(t_game *game)
{
	int		i;

	i = 0;
	clear_view(game);
	if (BONUS_F == 1)
		render_sky(game);
	while (i < game->cub.window_width)
	{
		render_wall_strip(i, game);
		i = i + 1;
	}
}
