/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:10:54 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/12 16:38:40 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_ray_direction(t_ray *ray)
{
	double angle;

	angle = ray->ray_angle;
	ray->facing_down = angle > 0 && angle < PI;
	ray->facing_up = !ray->facing_down;
	ray->facing_left = angle > PI / 2 && angle < 1.5 * PI;
	ray->facing_right = !ray->facing_left;
}

void	compare_distances(t_ray *ray, t_pl player)
{
	double hor_dist;
	double ver_dist;

	if (ray->hwall_hit == true)
		hor_dist = get_distance(player.x, player.y, ray->hwall_x, ray->hwall_y);
	else
		hor_dist = INT_MAX;
	if (ray->vwall_hit == true)
		ver_dist = get_distance(player.x, player.y, ray->vwall_x, ray->vwall_y);
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

void	search_first_collision_wall(t_game *game, int i)
{
	check_ray_direction(&game->rays[i]);
	check_horizontal_intersections(&game->rays[i], game->player, game->cub);
	check_vertical_intersection(&game->rays[i], game->player, game->cub);
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
