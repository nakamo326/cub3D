/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 23:20:57 by ynakamot          #+#    #+#             */
/*   Updated: 2020/11/30 10:54:18 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double degtorad(double deg)
{
	return (deg * (PI / 180.0));
}

double radtodeg(double rad)
{
	return (rad * (180.0 / PI));
}
