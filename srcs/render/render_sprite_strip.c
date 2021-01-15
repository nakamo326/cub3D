/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite_strip.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:10:29 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/15 11:07:42 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_sprite_texture(t_game *game, t_sprite *sp, double x_ratio, double y_ratio)
{
	int		x;
	int		y;
	int		color;
	char	*addr;
	t_tex	tex;

	if (BONUS_F == 1)
		tex = choose_sp_tex(sp, game);
	else
		tex = game->tex_sp;
	x = round(x_ratio * tex.width);
	y = round(y_ratio * tex.height);
	addr = (char *)tex.addr;
	color = *(int *)(addr + y * tex.len + x * (tex.bpp / 8));
	if (BONUS_F == 1)
		return (add_shadow(color, game , sp->corr_dist));
	return (color);
}

double	get_sprite_x(t_ray ray, t_sprite *sprite)
{
	double	size;
	double	result;

	if (sprite->left_angle > sprite->right_angle)
	{
		size = (TWO_PI - sprite->left_angle) + sprite->right_angle;
		if (ray.ray_angle < PI)
			result = ((TWO_PI - sprite->left_angle) + ray.ray_angle) / size;
		else
			result = (ray.ray_angle - sprite->left_angle) / size;
	}
	else
	{
		result = (ray.ray_angle - sprite->left_angle)
			/ (sprite->right_angle - sprite->left_angle);
	}
	return (result);
}

void	render_sprite_strip(t_game *game, t_sprite *sp, int i)
{
	double	sprite_size;
	int		sprite_start;
	double	x_ratio;
	double	y_ratio;
	int		j;

	sprite_size = (TILE_SIZE / sp->corr_dist) * (game->view.w / 2) / tan(FOV / 2);
	sprite_start = round((game->view.h / 2) - (sprite_size / 2));
	x_ratio = get_sprite_x(game->rays[i], sp);
	j = sprite_start > 0 ? sprite_start : 0;
	while (j < game->cub.window_height && j < sprite_size + sprite_start)
	{
		y_ratio = (j - sprite_start) / sprite_size;
		if (get_sprite_texture(game, sp, x_ratio, y_ratio) != 0x000000)
			my_mlx_pixel_put(&game->view, i, j,
				get_sprite_texture(game, sp, x_ratio, y_ratio));
		j++;
	}
}
