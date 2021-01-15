/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hitpoint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 16:40:46 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/15 21:02:33 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_lifebar_frame(t_game *game)
{
	int i;
	int end;

	i = game->view.h * 93 / 100;
	end = game->view.h * 98 / 100;
	while (i < end)
	{
		my_mlx_pixel_put(&game->view, game->view.w * 3 / 100 - 1, i, 0x012217);
		my_mlx_pixel_put(&game->view, game->view.w * 3 / 100, i, 0x012217);
		i++;
	}
	i = game->view.w * 3 / 100;
	while (i < game->view.w * 23 / 100)
	{
		my_mlx_pixel_put(&game->view, i, end, 0x012217);
		my_mlx_pixel_put(&game->view, i, end + 1, 0x012217);
		i++;
	}
}

void	render_hitpoint(t_game *game)
{
	int		i;
	int		j;
	double	len;

	len = game->view.w * 0.2 * (double)game->player.life * 0.01;
	len = len + game->view.w * 3 / 100;
	i = game->view.w * 3 / 100;
	while (i < len)
	{
		j = game->view.h * 94 / 100;
		while (j < game->view.h * 97 / 100)
		{
			my_mlx_pixel_put(&game->view, i, j, 0x00B007);
			j++;
		}
		i++;
	}
	render_lifebar_frame(game);
}
