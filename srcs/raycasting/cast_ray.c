/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:10:54 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/10 16:29:12 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, PI * 2);
	if (angle < 0)
	{
		angle = PI * 2 + angle;
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

void	compare_distances(t_game *game, int i)
{
	double hor_hit_dist;
	double ver_hit_dist;

	hor_hit_dist = sqrt((game->rays[i].hwall_x - game->player.x) *
					(game->rays[i].hwall_x - game->player.x) +
					(game->rays[i].hwall_y - game->player.y) *
					(game->rays[i].hwall_y - game->player.y));
	ver_hit_dist = sqrt((game->rays[i].vwall_x - game->player.x) *
					(game->rays[i].vwall_x - game->player.x) +
					(game->rays[i].vwall_y - game->player.y) *
					(game->rays[i].vwall_y - game->player.y));
	if (hor_hit_dist < ver_hit_dist || game->rays[i].vwall_hit == false)
	{
		game->rays[i].vwall_hit = false;
		game->rays[i].distance = hor_hit_dist;
		return ;
	}
	if (ver_hit_dist < hor_hit_dist || game->rays[i].hwall_hit == false)
	{
		game->rays[i].hwall_hit = false;
		game->rays[i].distance = ver_hit_dist;
		return ;
	}
	if (hor_hit_dist == ver_hit_dist)
	{
		game->rays[i].hwall_hit = false;
		game->rays[i].distance = ver_hit_dist;
		return ;
	}
}

void	check_horizontal_intersections(t_game *game, int i)
{
	double	x;
	double	y;
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;

	yintercept = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	if (game->rays[i].facing_down)
		yintercept += TILE_SIZE;
	xintercept = (yintercept - game->player.y) / tan(game->rays[i].ray_angle)
				+ game->player.x;
	ystep = TILE_SIZE;
	if (game->rays[i].facing_up)
		ystep *= -1;
	xstep = TILE_SIZE / tan(game->rays[i].ray_angle);
	if (game->rays[i].facing_left && xstep > 0)
		xstep *= -1;
	if (game->rays[i].facing_right && xstep < 0)
		xstep *= -1;
	x = xintercept;
	y = yintercept;
	game->rays[i].hwall_hit = false;
	while (x >= 0 && x <= game->cub.map_maxcol * TILE_SIZE &&
			y >= 0 && y <= game->cub.map_maxrow * TILE_SIZE)
	{
		if (game->rays[i].facing_up)
		{
			if (check_collision(game, x, y - 1))
			{
				game->rays[i].hwall_hit = true;
				game->rays[i].hwall_x = x;
				game->rays[i].hwall_y = y;
				break;
			}
		}
		else
		{
			if (check_collision(game, x, y))
			{
				game->rays[i].hwall_hit = true;
				game->rays[i].hwall_x = x;
				game->rays[i].hwall_y = y;
				break;
			}
		}
		x += xstep;
		y += ystep;
	}
}

void	check_vertical_intersection(t_game *game, int i)
{
	double	x;
	double	y;
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;

	xintercept = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += game->rays[i].facing_right ? TILE_SIZE : 0;
	yintercept = (xintercept - game->player.x) * tan(game->rays[i].ray_angle)
				+ game->player.y;
	xstep = TILE_SIZE;
	if (game->rays[i].facing_left)
		xstep *= -1;

	ystep = TILE_SIZE * tan(game->rays[i].ray_angle);
	if (game->rays[i].facing_up && ystep > 0)
		ystep *= -1;
	if (game->rays[i].facing_down && ystep < 0)
		ystep *= -1;
	x = xintercept;
	y = yintercept;
	game->rays[i].vwall_hit = false;
	while (x >= 0 && x <= game->cub.map_maxcol * TILE_SIZE &&
			y >= 0 && y <= game->cub.map_maxrow * TILE_SIZE)
	{
		if (game->rays[i].facing_left)
		{
			if (check_collision(game, x - 1, y))
			{
				game->rays[i].vwall_hit = true;
				game->rays[i].vwall_x = x;
				game->rays[i].vwall_y = y;
				break;
			}
		}
		else
		{
			if (check_collision(game, x, y))
			{
				game->rays[i].vwall_hit = true;
				game->rays[i].vwall_x = x;
				game->rays[i].vwall_y = y;
				break;
			}
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

	game->rays = malloc(sizeof(t_ray) * game->cub.window_width);
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
