/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:22:46 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/03 22:08:18 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_exit(char *errormsg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(errormsg, 2);
	exit(EXIT_FAILURE);
}

void	free_cub_info(void)
{
	int	i;

	if (cub.no_path != NULL)
		free(cub.no_path);
	if (cub.so_path != NULL)
		free(cub.so_path);
	if (cub.we_path != NULL)
		free(cub.we_path);
	if (cub.ea_path != NULL)
		free(cub.ea_path);
	i = 0;
	if (cub.map != NULL)
		while (cub.map[i] != NULL)
		{
			free(cub.map[i]);
			i++;
		}
}

void	config_error(int ret)
{
	const char err_msg[][40] = {
		{"Error in read function.\n"},
		{"Dummy for skip"},
		{"Error in malloc function.\n"},
		{"Identifier is duplicated.\n"},
		{"Invalid format.\n"},
		{"Invalid resolution.\n"},
		{"Invalid file path.\n"},
		{"Invalid color code.\n"},
		{"No map in cub file.\n"},
		{"Player position is duplicated.\n"},
		{"Map isn't closed.\n"}
	};

	free_cub_info();
	err_exit((char *)err_msg[ret]);
}
