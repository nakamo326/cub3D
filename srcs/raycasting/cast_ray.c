/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:10:54 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/21 01:11:28 by ynakamot         ###   ########.fr       */
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

void	check_ray_direction(t_ray *rays, int i)
{
	double angle;

	angle = rays[i].ray_angle;
	rays[i].facing_down = angle > 0 && angle < PI;
	rays[i].facing_up = !rays[i].facing_down;
	rays[i].facing_left = angle > PI / 2 && angle < 1.5 * PI;
	rays[i].facing_right = !rays[i].facing_left;
}

double get_distance_wall(double x0, double y0, double x1, double y1)
{
	double distance;

	distance = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
	return (distance);
}

void	compare_distances(t_game *game, int i)
{
	double hor_hit_dist;
	double ver_hit_dist;


	if (game->rays[i].hwall_hit == true)
		hor_hit_dist = get_distance_wall(game->player.x, game->player.y,
							game->rays[i].hwall_x, game->rays[i].hwall_y);
	else
		hor_hit_dist = INT_MAX;
	if (game->rays[i].vwall_hit == true)
		ver_hit_dist = get_distance_wall(game->player.x, game->player.y,
							game->rays[i].vwall_x, game->rays[i].vwall_y);
	else
		ver_hit_dist = INT_MAX;
	if (hor_hit_dist < ver_hit_dist)
	{
		game->rays[i].vwall_hit = false;
		game->rays[i].distance = hor_hit_dist;
	}
	else if (ver_hit_dist < hor_hit_dist)
	{
		game->rays[i].hwall_hit = false;
		game->rays[i].distance = ver_hit_dist;
	}
	return ;
}

void	check_horizontal_intersections(t_game *game, int i)
{
	double	x;
	double	y;
	double	x_intercept;
	double	y_intercept;
	double	xstep;
	double	ystep;
	double	x_check;
	double	y_check;

	y_intercept = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += game->rays[i].facing_down ? TILE_SIZE : 0;

	x_intercept = (y_intercept - game->player.y) / tan(game->rays[i].ray_angle)
				+ game->player.x;

	ystep = TILE_SIZE;
	ystep *= game->rays[i].facing_up ? -1 : 1;

	xstep = TILE_SIZE / tan(game->rays[i].ray_angle);
	if (game->rays[i].facing_left && xstep > 0)
		xstep *= -1;
	if (game->rays[i].facing_right && xstep < 0)
		xstep *= -1;

	x = x_intercept;
	y = y_intercept;
	game->rays[i].hwall_hit = false;
	while (x >= 0 && x <= game->cub.map_maxcol * TILE_SIZE &&
			y >= 0 && y <= game->cub.map_maxrow * TILE_SIZE)
	{
		x_check = x;
		y_check = y + (game->rays[i].facing_up ? -1 : 0);
		if (check_collision(game, x_check, y_check))
		{
			game->rays[i].hwall_hit = true;
			game->rays[i].hwall_x = x;
			game->rays[i].hwall_y = y;
			break;
		}
		x += xstep;
		y += ystep;
	}
}

void	check_vertical_intersection(t_game *game, int i)
{
	double	x;
	double	y;
	double	x_intercept;
	double	y_intercept;
	double	xstep;
	double	ystep;
	double	x_check;
	double	y_check;

	x_intercept = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	x_intercept += game->rays[i].facing_right ? TILE_SIZE : 0;
	y_intercept = (x_intercept - game->player.x) * tan(game->rays[i].ray_angle)
					+ game->player.y;
	xstep = TILE_SIZE;
	if (game->rays[i].facing_left)
		xstep *= -1;
	ystep = TILE_SIZE * tan(game->rays[i].ray_angle);
	if (game->rays[i].facing_up && ystep > 0)
		ystep *= -1;
	if (game->rays[i].facing_down && ystep < 0)
		ystep *= -1;
	x = x_intercept;
	y = y_intercept;
	game->rays[i].vwall_hit = false;
	while (x >= 0 && x <= game->cub.map_maxcol * TILE_SIZE &&
			y >= 0 && y <= game->cub.map_maxrow * TILE_SIZE)
	{
		x_check = x + (game->rays[i].facing_left ? -1 : 0);
		y_check = y;
		if (check_collision(game, x_check, y_check))
		{
			game->rays[i].vwall_hit = true;
			game->rays[i].vwall_x = x;
			game->rays[i].vwall_y = y;
			break;
		}
		x += xstep;
		y += ystep;
	}
}

void	search_first_collision_wall(t_game *game, int i)
{
	check_ray_direction(game->rays, i);
	check_horizontal_intersections(game, i);
	check_vertical_intersection(game, i);
	compare_distances(game, i);
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
