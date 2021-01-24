/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:07:56 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/24 13:27:07 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_tex	choose_texture(t_ray ray, t_game *game)
{
	t_tex	tex;

	if (ray.facing_up && ray.hwall_hit)
		tex = game->tex_n;
	if (ray.facing_down && ray.hwall_hit)
		tex = game->tex_s;
	if (ray.facing_right && ray.vwall_hit)
		tex = game->tex_e;
	if (ray.facing_left && ray.vwall_hit)
		tex = game->tex_w;
	return (tex);
}

int		get_wall_texture(t_game *game, int i, double x_ratio, double y_ratio)
{
	int		x;
	int		y;
	int		color;
	char	*addr;
	t_tex	tex;

	tex = choose_texture(game->rays[i], game);
	x = round(x_ratio * tex.width);
	y = round(y_ratio * tex.height);
	addr = (char *)tex.addr;
	color = *(int *)(addr + y * tex.len + x * (tex.bpp / 8));
	if (BONUS_F == 1)
		return (add_shadow(color, game->zbuffer[i]));
	return (color);
}
