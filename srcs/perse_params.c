/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:57:40 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/01 10:34:41 by ynakamot         ###   ########.fr       */
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
		if (!(line[i] == ' ' || ft_isdigit(line[i++])))
			return (INVALID_FORMAT);
	if (!(strs = ft_split(line, ' ')))
		return (MALLOC_ERROR);
	tmp = ft_atoi(strs[0]);
	cub_info.window_width = tmp;
	tmp = ft_atoi(strs[1]);
	cub_info.window_height = tmp;
	ft_free_split(strs);
	if (cub_info.window_width <= 0 || cub_info.window_height <= 0)
		return (INVALID_RESO);
	cub_info.win_f = true;
	return (SUCCESS);
}

int		input_path(char *line, int identifier)
{
	char	*path;
	int		fd;
	int		rc;
	//pathのチェックは後でまとめてやる
	//エラーだったらpathのfree必要（free_cub_info
	if (!(path = ft_strtrim(line, " ")))
		return (MALLOC_ERROR);
	if (identifier == NO)
		cub_info.no_path = path;
	if (identifier == SO)
		cub_info.so_path = path;
	if (identifier == WE)
		cub_info.we_path = path;
	if (identifier == EA)
		cub_info.ea_path = path;
	if (identifier == S)
		cub_info.sp_path = path;
	set_flag(identifier);
	return (SUCCESS);
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
		if (rgb[i] < 0 || rgb[i++] > 255)
			return (free_ret(strs, INVALID_COLOR));
		if (identifier == F)
			cub_info.f_color[i] = rgb[i++];
		if (identifier == C)
			cub_info.c_color[i] = rgb[i++];
	}
	set_flag(identifier);
	return (SUCCESS);
}

int		free_ret(char **strs, int ret)
{
	ft_free_split(strs);
	return (ret);
}

int		set_flag(int identifier)
{
	if (identifier == NO)
		cub_info.no_path_f = true;
	if (identifier == SO)
		cub_info.so_path_f = true;
	if (identifier == WE)
		cub_info.we_path_f = true;
	if (identifier == EA)
		cub_info.ea_path_f = true;
	if (identifier == S)
		cub_info.sp_path_f = true;
	if (identifier == F)
		cub_info.f_color_f = true;
	if (identifier == C)
		cub_info.c_color_f = true;
	return (ERROR);
}