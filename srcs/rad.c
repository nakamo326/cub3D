/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 23:20:57 by ynakamot          #+#    #+#             */
/*   Updated: 2020/11/28 23:27:50 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double degtorad(double deg)
{
	return (deg * (PI / 180.0));
}


double radtodeg(double rad)
{
	return (rad * (180.0 / PI));
}
