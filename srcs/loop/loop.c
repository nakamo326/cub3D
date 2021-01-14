/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 15:06:12 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/14 22:24:17 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_frame(t_game *game)
{
	game->frame++;
	if(game->frame == 5)
		game->frame = 0;
}

int		loop(t_game *game)
{
	move_player(game);
	cal_item_info(game->cub.items, game->player);
	cast_all_rays(game);
	render_projected_wall(game);
	cal_shot(game);
	render_sprite(game);
	if (BONUS_F == 1)
	{
		render_minimap(game);
		update_frame(game);
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->view.img_ptr, 0, 0);
	mlx_do_sync(game->mlx);
	return (SUCCESS);
}
