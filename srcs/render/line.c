/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:07:55 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/07 12:58:30 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_fabs(double n)
{
	if (n > 0)
		return (n);
	return (-n);
}

void	ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

//void	draw_line(t_game *game, int x0, int x1, int y0, int y1)
//{
//	double	delta;
//	double	error;
//	double	d_error;
//	int		x;
//	int		y;
//
//
//	y = y1 - y0;
//	x = x1 - x0;
//	delta = (double)y / x;
//	d_error = ft_fabs(delta);
//	error = 0;
//	y = y0;
//	x = x0;
//
//	while (x <= x1)
//	{
//		my_mlx_pixel_put(&game->map, x, y, 0x50FFFF00);
//		error = error + d_error;
//		if (error >= 0.5)
//		{
//			y++;
//			error = error - 1;
//		}
//		x++;
//	}
//}

void	draw_line(t_game *game, int x0, int x1, int y0, int y1)
{
	bool	steep;
	int	deltax;
	int	deltay;
	int	error;
	int		ystep;
	int		x;
	int		y;

	steep = ft_abs(y1 - y0) > ft_abs(x1 - x0);
	if (steep)
	{
		ft_swap(&x0, &y0);
		ft_swap(&x1, &y1);
	}
	if (x0 > x1)
	{
		ft_swap(&x0, &x1);
		ft_swap(&y0, &y1);
	}

	deltax = x1 - x0;
	deltay = ft_abs(y1 - y0);
	error = deltax / 2;

	y = y0;
	x = x0;
	ystep = y1 > y0 ? 1 : -1;
	while (x <= x1)
	{

		if (steep)
			my_mlx_pixel_put(&game->map, y, x, 0x50FFFF00);
		else
			my_mlx_pixel_put(&game->map, x, y, 0x50FFFF00);
		error = error - deltay;
		if (error < 0)
		{
			y += ystep;
			error = error + deltax;
		}
		x++;
	}
}

//void	draw_line(t_game *game, int x0, int x1, int y0, int y1)
//{
//
//}