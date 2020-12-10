/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 15:06:12 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/10 15:37:57 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop(t_game *game)
{
	move_player(game);
	cast_all_rays(game);
	render_projected_wall(game);
	render_minimap(game);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->view.img_ptr, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->map.img_ptr, 0, 0);
	mlx_do_sync(game->mlx);
	return (SUCCESS);
}