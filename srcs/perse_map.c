/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:40:17 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/01 15:45:33 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_validmapline(char *line)
{
	//return MAP
	int ret;
	const char *mapchar = "012NSEW ";

	if ((ret = check_identifier(line)) != MAP)
		return (INVALID_FORMAT);
	while ()


}