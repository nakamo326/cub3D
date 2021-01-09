/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:10:54 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/09 10:17:54 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return (angle);
}

void	check_ray_direction(t_ray *ray)
{
	double angle;

	angle = ray->ray_angle;
	ray->facing_down = angle > 0 && angle < PI;
	ray->facing_up = !ray->facing_down;
	ray->facing_left = angle > PI / 2 && angle < 1.5 * PI;
	ray->facing_right = !ray->facing_left;
}

void	check_hor_intersection(t_ray *ray, t_pl player)
{
	if (ray->hwall_hit == false)
		return;
	if ((ray->facing_up && (ray->hwall_y <= player.y) == false) ||
		(ray->facing_down && (ray->hwall_y >= player.y) == false) ||
		(ray->facing_right && (ray->hwall_x >= player.x) == false) ||
		(ray->facing_left && (ray->hwall_x <= player.x) == false))
	{
		ray->hwall_hit = false;
		return ;
	}
	return ;
}

void	check_ver_intersection(t_ray *ray, t_pl player)
{
	//check intersection position is correct
	if (ray->vwall_hit == false)
		return;
	if ((ray->facing_up && (ray->vwall_y <= player.y) == false) ||
		(ray->facing_down && (ray->vwall_y >= player.y) == false) ||
		(ray->facing_right && (ray->vwall_x >= player.x) == false) ||
		(ray->facing_left && (ray->vwall_x <= player.x) == false))
	{
		ray->vwall_hit = false;
		return ;
	}
	return ;
}

double	get_distance(double x0, double y0, double x1, double y1)
{
	double distance;

	distance = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
	return (distance);
}

void	compare_distances(t_ray *ray, t_pl player)
{
	double hor_dist;
	double ver_dist;

	if (ray->hwall_hit == true)
		hor_dist = get_distance(player.x, player.y,ray->hwall_x, ray->hwall_y);
	else
		hor_dist = INT_MAX;
	if (ray->vwall_hit == true)
		ver_dist = get_distance(player.x, player.y,ray->vwall_x, ray->vwall_y);
	else
		ver_dist = INT_MAX;
	if (hor_dist < ver_dist)
	{
		ray->vwall_hit = false;
		ray->distance = hor_dist;
	}
	else if (ver_dist < hor_dist)
	{
		ray->hwall_hit = false;
		ray->distance = ver_dist;
	}
	return ;
}

void	check_horizontal_intersections(t_ray *ray, t_pl player, t_cub cub)
{
	double	x;
	double	y;
	double	xstep;
	double	ystep;
	double	x_check;
	double	y_check;

	y = floor(player.y / TILE_SIZE) * TILE_SIZE;
	y += ray->facing_down ? TILE_SIZE : 0;
	x = (y - player.y) / tan(ray->ray_angle) + player.x;
	ystep = TILE_SIZE;
	ystep *= ray->facing_up ? -1 : 1;
	xstep = TILE_SIZE / tan(ray->ray_angle);
	if (ray->facing_left && xstep > 0)
		xstep *= -1;
	if (ray->facing_right && xstep < 0)
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
			break;
		}
		x += xstep;
		y += ystep;
	}
}

void	check_vertical_intersection(t_ray *ray, t_pl player, t_cub cub)
{
	double	x;
	double	y;
	double	xstep;
	double	ystep;
	double	x_check;
	double	y_check;

	x = floor(player.x / TILE_SIZE) * TILE_SIZE;
	x += ray->facing_right ? TILE_SIZE : 0;
	y = (x - player.x) * tan(ray->ray_angle) + player.y;
	xstep = TILE_SIZE;
	if (ray->facing_left)
		xstep *= -1;
	ystep = TILE_SIZE * tan(ray->ray_angle);
	if (ray->facing_up && ystep > 0)
		ystep *= -1;
	if (ray->facing_down && ystep < 0)
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
			break;
		}
		x += xstep;
		y += ystep;
	}
}

void	search_first_collision_wall(t_game *game, int i)
{
	check_ray_direction(&game->rays[i]);
	check_horizontal_intersections(&game->rays[i], game->player, game->cub);
	check_vertical_intersection(&game->rays[i], game->player, game->cub);
	check_hor_intersection(&game->rays[i], game->player);
	check_ver_intersection(&game->rays[i], game->player);
	compare_distances(&game->rays[i], game->player);
}

void	cast_all_rays(t_game *game)
{
	double	start_angle;
	double	angle_per_pixel;
	double	ray_angle;
	int		i;

	ft_bzero(game->rays, (size_t)game->cub.window_width * sizeof(t_ray));
	start_angle = game->player.rotation_angle - FOV / 2;
	angle_per_pixel = FOV / game->cub.window_width;
	i = 0;
	ray_angle = start_angle;
	while (i < game->cub.window_width)
	{
		game->rays[i].ray_angle = normalize_angle(ray_angle);
		search_first_collision_wall(game, i);
		ray_angle += angle_per_pixel;
		i++;
	}
}
