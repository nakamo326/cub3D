/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:22:46 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/08 14:53:16 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_exit(char *errormsg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(errormsg, 2);
	exit(EXIT_FAILURE);
}

void	config_error(int ret)
{
	const char err_msg[][40] = {
		{"Error in read function.\n"},
		{"Dummy for skip"},
		{"Error in memory allocation.\n"},
		{"argument is wrong.\n"},
		{"file is not cub file.\n"},
		{"Identifier is duplicated.\n"},
		{"Invalid format.\n"},
		{"Invalid resolution.\n"},
		{"Invalid file path.\n"},
		{"Invalid color code.\n"},
		{"No map in cub file.\n"},
		{"Player's position is duplicated.\n"},
		{"No player is in map.\n"},
		{"Map isn't closed.\n"}
	};

	err_exit((char *)err_msg[ret]);
}
