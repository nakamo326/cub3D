/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:34:25 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/12 13:35:27 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_floor_texture(t_game *game, double x_ratio, double y_ratio)
{
	int		color;
	char	*addr;
	t_tex	tex;
	int		x;
	int		y;

	tex = game->tex_w;
	x = round(x_ratio * tex.width);
	y = round(y_ratio * tex.height);
	addr = (char *)tex.addr;
	color = *(int *)(addr + y * tex.len + x * (tex.bpp / 8));
	return (color);
}

void	render_floor(t_game *game, double dist_plane, int i, int j)
{
	int		color;
	double	x;
	double	y;
	double	correct_distance;
	double	ratio;

	ratio = game->player.z * dist_plane;
	while (j < game->cub.window_height)
	{
		correct_distance = ratio / (j - game->cub.window_height / 2)
			/ cos(game->rays[i].ray_angle - game->player.rotation_angle);
		x = game->player.x + correct_distance * cos(game->rays[i].ray_angle);
		y = game->player.y + correct_distance * sin(game->rays[i].ray_angle);
		color = get_floor_texture(game, fmod(x, TILE_SIZE) / TILE_SIZE,
										fmod(y, TILE_SIZE) / TILE_SIZE);
		my_mlx_pixel_put(&game->view, i, j, color);
		j++;
	}
}
