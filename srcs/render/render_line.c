/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:07:55 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/12 13:15:27 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

bool	exchange_quadrant(t_line *line)
{
	bool steep;

	steep = ft_abs(line->y1 - line->y0) > ft_abs(line->x1 - line->x0);
	if (steep)
	{
		ft_swap(&line->x0, &line->y0);
		ft_swap(&line->x1, &line->y1);
	}
	if (line->x0 > line->x1)
	{
		ft_swap(&line->x0, &line->x1);
		ft_swap(&line->y0, &line->y1);
	}
	return (steep);
}

void	draw_line(t_game *game, t_line line, int color)
{
	int	error;
	int	ystep;

	line.steep = exchange_quadrant(&line);
	line.delta_x = line.x1 - line.x0;
	line.delta_y = ft_abs(line.y1 - line.y0);
	error = line.delta_x / 2;
	ystep = line.y1 > line.y0 ? 1 : -1;
	while (line.x0 <= line.x1)
	{
		if (line.steep)
			my_mlx_pixel_put(&game->view, line.y0, line.x0, color);
		else
			my_mlx_pixel_put(&game->view, line.x0, line.y0, color);
		error = error - line.delta_y;
		if (error < 0)
		{
			line.y0 += ystep;
			error += line.delta_x;
		}
		line.x0++;
	}
}
