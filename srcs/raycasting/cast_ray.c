/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:10:54 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/08 13:33:43 by ynakamot         ###   ########.fr       */
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

void	check_ray_direction(t_game *game, int i)
{
	double angle;

	angle = game->rays[i].ray_angle;
	game->rays[i].facing_down = angle > 0 && angle < PI;
	game->rays[i].facing_up = !game->rays[i].facing_down;
	game->rays[i].facing_right = angle < PI / 2 || angle > 3 / 2 * PI;
	game->rays[i].facing_left = !game->rays[i].facing_right;
}

//serching  and compare two collision
void	check_horizontal_intersections(t_game *game, int i)
{
	double	x;
	double	y;
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;

	yintercept = (game->player.y / TILE_SIZE) * TILE_SIZE;
	if (game->rays[i].facing_down)
		yintercept += TILE_SIZE;
	xintercept = (game->player.y - yintercept) / tan(game->rays[i].ray_angle) + game->player.x;
	ystep = TILE_SIZE;
	if (game->rays[i].facing_up)
		ystep *= -1;
	xstep = ystep / tan(game->rays[i].ray_angle);
	if (game->rays[i].facing_left && xstep > 0)
		xstep *= -1;
	if (game->rays[i].facing_right && xstep < 0)
		xstep *= -1;
	x = xintercept;
	y = yintercept;
	if (game->rays[i].facing_up)
		x--;
	while (x >= 0 && x <= game->cub.map_maxcol * TILE_SIZE &&
			y >= 0 && y <= game->cub.map_maxrow * TILE_SIZE)
	{
		if (check_collision(game, x, y))
		{
			game->rays[i].wall_x = x;
			game->rays[i].wall_y = y;
			break;
		}
		x += xstep;
		y += ystep;
	}

}

void	search_first_collision_wall(t_game *game, int i)
{
	check_ray_direction(game, i);
	check_horizontal_intersections(game, i);
}

void	cast_all_rays(t_game *game)
{
	double	start_angle;
	double	angle_per_pixel;
	double	ray_angle;
	int		i;

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
