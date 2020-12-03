/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:57:40 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/03 22:09:21 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		input_resolution(char *line)
{
	int		i;
	int		tmp;
	char	**strs;

	i = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' || ft_isdigit(line[i])))
			return (INVALID_FORMAT);
		i++;
	}
	if (!(strs = ft_split(line, ' ')))
		return (MALLOC_ERROR);
	tmp = ft_atoi(strs[0]);
	cub.window_width = tmp;
	tmp = ft_atoi(strs[1]);
	cub.window_height = tmp;
	ft_free_split(strs);
	if (cub.window_width <= 0 || cub.window_height <= 0)
		return (INVALID_RESO);
	cub.win_f = true;
	return (SUCCESS);
}

int		input_path(char *line, int identifier)
{
	char	*path;
	//pathのチェックは後でまとめてやる
	if (!(path = ft_strtrim(line, " ")))
		return (MALLOC_ERROR);
	if (identifier == NO)
		cub.no_path = path;
	if (identifier == SO)
		cub.so_path = path;
	if (identifier == WE)
		cub.we_path = path;
	if (identifier == EA)
		cub.ea_path = path;
	if (identifier == S)
		cub.sp_path = path;
	set_flag(identifier);
	return (SUCCESS);
}

int		free_ret(char **strs, int ret)
{
	ft_free_split(strs);
	return (ret);
}

int		input_color(char *line, int identifier)
{
	char	**strs;
	int		i;
	int		rgb[3];

	if (!(strs = ft_split(line, ',')))
		return (MALLOC_ERROR);
	i = 0;
	while (i < 3)
	{
		if (strs[i] == NULL)
			return (free_ret(strs, INVALID_FORMAT));
		rgb[i] = ft_atoi(strs[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free_ret(strs, INVALID_COLOR));
		if (identifier == F)
			cub.f_color[i] = rgb[i];
		if (identifier == C)
			cub.c_color[i] = rgb[i];
		i++;
	}
	set_flag(identifier);
	return (free_ret(strs, SUCCESS));
}

int		set_flag(int identifier)
{
	if (identifier == NO)
		cub.no_path_f = true;
	if (identifier == SO)
		cub.so_path_f = true;
	if (identifier == WE)
		cub.we_path_f = true;
	if (identifier == EA)
		cub.ea_path_f = true;
	if (identifier == S)
		cub.sp_path_f = true;
	if (identifier == F)
		cub.f_color_f = true;
	if (identifier == C)
		cub.c_color_f = true;
	return (ERROR);
}