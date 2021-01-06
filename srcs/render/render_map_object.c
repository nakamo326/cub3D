/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 12:18:39 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/05 16:32:55 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(t_game *game, int x, int y)
{
	t_line line;

	line.x0 = x;
	line.y0 = y;
	line.x1 = round(x + cos(game->player.rotation_angle) * 10);
	line.y1 = round(y + sin(game->player.rotation_angle) * 10);
	draw_line(game, line, 0xFF0000);
	//red dot with anti alias
	my_mlx_pixel_put(&game->view, x, y, 0xFF0000);
	my_mlx_pixel_put(&game->view, x + 1, y, 0xFF0000);
	my_mlx_pixel_put(&game->view, x - 1, y, 0xFF0000);
	my_mlx_pixel_put(&game->view, x, y + 1, 0xFF0000);
	my_mlx_pixel_put(&game->view, x, y - 1, 0xFF0000);
	my_mlx_pixel_put(&game->view, x - 1, y - 1, 0x80110B);
	my_mlx_pixel_put(&game->view, x - 1, y + 1, 0x80110B);
	my_mlx_pixel_put(&game->view, x + 1, y - 1, 0x80110B);
	my_mlx_pixel_put(&game->view, x + 1, y + 1, 0x80110B);
}

void	render_ray(t_game *game)
{
	t_line		line;
	int			i;
	double		scale;

	scale = game->cub.map_scale;
	i = 0;
	while(i < game->cub.window_width)
	{
		line.x0 = game->player.x * scale;
		line.y0 = game->player.y * scale;
		if (game->rays[i].hwall_hit == true)
		{
			line.x1 = round(game->rays[i].hwall_x * scale);
			line.y1 = round(game->rays[i].hwall_y * scale);
			draw_line(game, line, 0x50FFFF00);
		}
		if (game->rays[i].vwall_hit == true)
		{
			line.x1 = round(game->rays[i].vwall_x * scale);
			line.y1 = round(game->rays[i].vwall_y * scale);
			draw_line(game, line, 0x50FFFF00);
		}
	i++;
	}
}

void	render_items(t_game *game, t_sprite item)
{
	double	scale;
	double	item_size;
	t_line	line;

	scale = game->cub.map_scale;
	item_size = TILE_SIZE * scale;
	line.x0 = item.x * scale + cos(item.angle + PI / 2) * item_size / 2;
	line.y0 = item.y * scale + sin(item.angle + PI / 2) * item_size / 2;
	line.x1 = item.x * scale + cos(item.angle - PI / 2) * item_size / 2;
	line.y1 = item.y * scale + sin(item.angle - PI / 2) * item_size / 2;
	draw_line(game, line, 0x2DC8FF);
}

void	render_map_object(t_game *game)
{
	t_list		*lstptr;
	t_sprite	*item_info;
	double		scale;

	scale = game->cub.map_scale;
	render_ray(game);
	lstptr = game->cub.items;
	while (lstptr != NULL)
	{
		item_info = lstptr->content;
		render_items(game, *item_info);
		lstptr = lstptr->next;
	}
	render_player(game, game->player.x * scale, game->player.y * scale);

}