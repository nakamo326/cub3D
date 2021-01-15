/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:15:23 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/15 11:03:54 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_angle_in_sprite(double angle, t_sprite *sprite)
{
	if (sprite->left_angle > sprite->right_angle)
	{
		if ((angle >= sprite->left_angle && angle <= TWO_PI) ||
		(angle >= 0 && angle <= sprite->right_angle))
			return (true);
	}
	else
	{
		if (angle >= sprite->left_angle && angle <= sprite->right_angle)
			return (true);
	}
	return (false);
}

void	projection_sprite(t_game *game, t_sprite *sprite)
{
	int	i;

	sprite->corr_dist = sprite->distance
		* cos(sprite->angle - game->player.rotation_angle);
	i = 0;
	while (i < game->cub.window_width)
	{
		if (game->zbuffer[i] > sprite->corr_dist &&
				is_angle_in_sprite(game->rays[i].ray_angle, sprite))
			render_sprite_strip(game, sprite, i);
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
