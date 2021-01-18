/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 15:06:12 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/18 13:12:05 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_frame(t_game *game)
{
	if (game->frame == 5)
		game->frame = 0;
	game->frame++;
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
		if (game->cub.map_scale != -1)
			render_minimap(game);
		render_reticle(game);
		render_hitpoint(game);
		update_frame(game);
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->view.img_ptr, 0, 0);
	if (BONUS_F == 1)
		put_hp_num(game);
	mlx_do_sync(game->mlx);
	return (SUCCESS);
}
