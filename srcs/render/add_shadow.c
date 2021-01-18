/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shadow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:14:23 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/18 13:17:04 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		add_shadow(int color, t_game *game, double dist)
{
	int	ratio;
	int	rgb[3];

	ratio = 100 - (int)(dist / game->dist_plane * 100);
	if (ratio < 0)
		ratio = 0;
	rgb[0] = get_color('r', color) * ratio / 100;
	rgb[1] = get_color('g', color) * ratio / 100;
	rgb[2] = get_color('b', color) * ratio / 100;
	return (create_trgb(0, rgb[0], rgb[1], rgb[2]));
}
