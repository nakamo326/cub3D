/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:38:11 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/12 21:06:19 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_horizontal_collision(double x, double y, t_cub cub, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	x_check;
	double	y_check;

	ystep = ray->facing_up ? -TILE_SIZE : TILE_SIZE;
	xstep = TILE_SIZE / tan(ray->ray_angle);
	if ((ray->facing_left && xstep > 0) || (ray->facing_right && xstep < 0))
		xstep *= -1;
	ray->hwall_hit = false;
	while (x >= 0 && x <= cub.map_maxcol * TILE_SIZE &&
			y >= 0 && y <= cub.map_maxrow * TILE_SIZE)
	{
		x_check = x;
		y_check = y + (ray->facing_up ? -1 : 0);
		if (check_collision(cub, x_check, y_check))
		{
			ray->hwall_hit = true;
			ray->hwall_x = x;
			ray->hwall_y = y;
			break ;
		}
		x += xstep;
		y += ystep;
	}
}

void	check_horizontal_intersections(t_ray *ray, t_pl player, t_cub cub)
{
	double	x;
	double	y;

	y = floor(player.y / TILE_SIZE) * TILE_SIZE;
	y += ray->facing_down ? TILE_SIZE : 0;
	x = (y - player.y) / tan(ray->ray_angle) + player.x;
	is_horizontal_collision(x, y, cub, ray);
}

void	is_vertical_collision(double x, double y, t_cub cub, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	x_check;
	double	y_check;

	xstep = ray->facing_left ? -TILE_SIZE : TILE_SIZE;
	ystep = TILE_SIZE * tan(ray->ray_angle);
	if ((ray->facing_up && ystep > 0) || (ray->facing_down && ystep < 0))
		ystep *= -1;
	ray->vwall_hit = false;
	while (x >= 0 && x <= cub.map_maxcol * TILE_SIZE &&
			y >= 0 && y <= cub.map_maxrow * TILE_SIZE)
	{
		x_check = x + (ray->facing_left ? -1 : 0);
		y_check = y;
		if (check_collision(cub, x_check, y_check))
		{
			ray->vwall_hit = true;
			ray->vwall_x = x;
			ray->vwall_y = y;
			break ;
		}
		x += xstep;
		y += ystep;
	}
}

void	check_vertical_intersection(t_ray *ray, t_pl player, t_cub cub)
{
	double	x;
	double	y;

	x = floor(player.x / TILE_SIZE) * TILE_SIZE;
	x += ray->facing_right ? TILE_SIZE : 0;
	y = (x - player.x) * tan(ray->ray_angle) + player.y;
	is_vertical_collision(x, y, cub, ray);
}
