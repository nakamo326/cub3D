/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:12:49 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/12 13:33:42 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_valid_args(int argc, char *argv[], t_game *game)
{
	int	fd;

	if (argc <= 1 || argc >= 4)
		config_error(INVALID_ARG);
	if (!is_cub(argv[1]))
		config_error(ISNT_CUBFILE);
	if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
		game->save_flag = true;
	if ((fd = open(argv[1], O_RDONLY)) == ERROR)
		exit(EXIT_FAILURE);
}
