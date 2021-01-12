/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:58:10 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/12 13:03:08 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cal_item_info(t_list *items, t_pl player)
{
	t_sprite	*sp;

	while (items)
	{
		sp = (t_sprite *)items->content;
		sp->distance = get_distance(player.x, player.y, sp->x, sp->y);
		sp->angle = normalize_angle(
			atan2(sp->y - player.y, sp->x - player.x));
		sp->right_cor[0] = sp->x + cos(sp->angle + PI / 2) * TILE_SIZE / 2;
		sp->right_cor[1] = sp->y + sin(sp->angle + PI / 2) * TILE_SIZE / 2;
		sp->right_angle = normalize_angle(atan2(
			sp->right_cor[1] - player.y, sp->right_cor[0] - player.x));
		sp->left_cor[0] = sp->x + cos(sp->angle - PI / 2) * TILE_SIZE / 2;
		sp->left_cor[1] = sp->y + sin(sp->angle - PI / 2) * TILE_SIZE / 2;
		sp->left_angle = normalize_angle(atan2(
			sp->left_cor[1] - player.y, sp->left_cor[0] - player.x));
		items = items->next;
	}
}

void	is_visible_sprite(t_game *game)
{
	t_list		*lst_p;
	t_sprite	*tmp;
	double		start_angle;

	lst_p = game->cub.items;
	start_angle = game->player.rotation_angle - FOV / 2;
	while (lst_p != NULL)
	{
		tmp = lst_p->content;
		if (tmp->left_angle >= start_angle && tmp->left_angle <= start_angle + FOV)
			tmp->visible = true;
		else if (tmp->right_angle >= start_angle && tmp->right_angle <= start_angle + FOV)
			tmp->visible = true;
		else if (tmp->left_angle <= start_angle && tmp->right_angle >= start_angle + FOV)
			tmp->visible = true;
		else
			tmp->visible = false;
		lst_p = lst_p->next;
	}
}
