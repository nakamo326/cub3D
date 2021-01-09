/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 15:06:12 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/09 10:45:51 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop(t_game *game)
{
	move_player(game);
	cal_item_info(game->cub.items, game->player);
	is_visible_sprite(game);
	cast_all_rays(game);
	render_projected_wall(game);
	render_sprite(game);
	render_minimap(game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->view.img_ptr, 0, 0);
	//while (1);
	mlx_do_sync(game->mlx);
	return (SUCCESS);
}