/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_reticle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 23:47:37 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/15 12:18:23 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_reticle(t_game *game)
{
	int x;
	int y;

	x = game->view.w / 2;
	y = game->view.h / 2;
	my_mlx_pixel_put(&game->view, x, y, 0xFF0000);
	my_mlx_pixel_put(&game->view, x + 1, y, 0xFF0000);
	my_mlx_pixel_put(&game->view, x + 2, y, 0xFF0000);
	my_mlx_pixel_put(&game->view, x + 3, y, 0xFF0000);
	my_mlx_pixel_put(&game->view, x - 1, y, 0xFF0000);
	my_mlx_pixel_put(&game->view, x - 2, y, 0xFF0000);
	my_mlx_pixel_put(&game->view, x - 3, y, 0xFF0000);
	my_mlx_pixel_put(&game->view, x, y + 1, 0xFF0000);
	my_mlx_pixel_put(&game->view, x, y + 2, 0xFF0000);
	my_mlx_pixel_put(&game->view, x, y + 3, 0xFF0000);
	my_mlx_pixel_put(&game->view, x, y - 1, 0xFF0000);
	my_mlx_pixel_put(&game->view, x, y - 2, 0xFF0000);
	my_mlx_pixel_put(&game->view, x, y - 3, 0xFF0000);
}
