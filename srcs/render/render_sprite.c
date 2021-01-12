/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:15:23 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/12 16:15:24 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_ray_in_sprite(t_ray ray, t_sprite *sprite)
{
	if (sprite->left_angle > sprite->right_angle)
	{
		if ((ray.ray_angle >= sprite->left_angle && ray.ray_angle <= TWO_PI) ||
		(ray.ray_angle >= 0 && ray.ray_angle <= sprite->right_angle))
			return (true);
	}
	else
	{
		if (ray.ray_angle >= sprite->left_angle &&
				ray.ray_angle <= sprite->right_angle)
			return (true);
	}
	return (false);
}

void	projection_sprite(t_game *game, t_sprite *sprite)
{
	double	correct_distance;
	int		i;

	correct_distance = sprite->distance
		* cos(sprite->angle - game->player.rotation_angle);
	i = 0;
	while (i < game->cub.window_width)
	{
		if (game->zbuffer[i] > correct_distance &&
				is_ray_in_sprite(game->rays[i], sprite))
			render_sprite_strip(game, sprite, i, correct_distance);
		i++;
	}
}

void	render_sprite(t_game *game)
{
	t_list		*lst_p;
	t_sprite	*sprite;

	sort_items(game->cub.items);
	lst_p = game->cub.items;
	while (lst_p != NULL)
	{
		sprite = lst_p->content;
		projection_sprite(game, sprite);
		lst_p = lst_p->next;
	}
}
