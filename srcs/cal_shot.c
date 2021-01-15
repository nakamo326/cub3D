/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_shot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 22:21:15 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/14 23:08:23 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//segfo suruyo

void	cal_shot(t_game *game)
{
	int			i;
	int			num;
	t_list		*items;
	t_sprite	*item_info;

	if (game->shot == false)
		return ;
	items = game->cub.items;
	i = 0;
	while (items != NULL)
	{
		item_info = (t_sprite *)items->content;
		if (is_angle_in_sprite(game->player.rotation_angle, item_info))
			num = i;
		items = items->next;
		i++;
	}
	items = game->cub.items;
	i = 0;
	while (items != NULL)
	{
		if (i == num)
		{
			item_info = (t_sprite *)items->content;
			if (item_info->life > 0)
				item_info->life -= 1;
			break ;
		}
		items = items->next;
		i++;
	}
	game->shot = false;
	return ;
}
