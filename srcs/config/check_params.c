/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 11:01:47 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/20 14:44:26 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_cub(char *filepath)
{
	size_t len;

	len = ft_strlen(filepath);
	if (len > 4 || ft_strncmp(&filepath[len - 4], ".cub" , 4) == 0)
		return (SUCCESS);
	return (0);
}

//void	is_valid_resolution(t_game *game)
//{
//	//if window's resolution is over display's resolution,adjust it and return.not error.
//}
//
//void	check_missing_params(t_game *game)
//{
//
//}
//
//void	is_valid_filepath(t_game *game)
//{
//
//}
//
//int	check_valid_params(t_game *game)
//{
//	//is_valid_resolution(game);
//	//is_valid_filepath(game);
//	//check_missing_params(game);
//
//}