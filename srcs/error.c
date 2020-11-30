/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:22:46 by ynakamot          #+#    #+#             */
/*   Updated: 2020/11/30 22:24:12 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_exit(char *errormsg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(errormsg, 2);
	exit (EXIT_FAILURE);
}

void	free_cub_info()
{
	int	i;

	if (cub_info.no_path != NULL)
		free(cub_info.no_path);
	if (cub_info.so_path != NULL)
		free(cub_info.so_path);
	if (cub_info.we_path != NULL)
		free(cub_info.we_path);
	if (cub_info.ea_path != NULL)
		free(cub_info.ea_path);
	i = 0;
	if (cub_info.map != NULL)
		while (cub_info.map[i] != NULL)
		{
			free(cub_info.map[i]);
			i++;
		}
}

void	config_error(int ret)
{
	const char err_msg[][30] = {
		{"Error in read function.\n"},
		{"dummy for skip"},
		{"Invalid format.\n"},
		{"Invalid resolution.\n"}
	};

	free_cub_info();
	err_exit(err_msg[ret]);
}
