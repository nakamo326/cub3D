/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 15:38:39 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/05 15:45:23 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + ( y * data->len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		get_color(char c, int trgb)
{
	if (c == 't')
		return (trgb & (0xFF << 24));
	if (c == 'r')
		return (trgb & (0xFF << 16));
	if (c == 'g')
		return (trgb & (0xFF << 8));
	if (c == 'b')
		return (trgb & 0xFF);
	return (ERROR);
}