/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:57:40 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/15 22:17:33 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		input_resolution(char *line, t_cub *cub)
{
	int		i;
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
	if (check_str_num(strs) != 2)
		return (INVALID_FORMAT);
	cub->window_width = ft_atoi(strs[0]);
	cub->window_height = ft_atoi(strs[1]);
	ft_free_split(strs);
	if (cub->window_width <= 0 || cub->window_height <= 0)
		return (INVALID_RESO);
	cub->win_f = true;
	return (SUCCESS);
}

int		input_path(char *line, int identifier, t_cub *cub)
{
	char	*path;

	if (!(path = ft_strtrim(line, " ")))
		return (MALLOC_ERROR);
	if (identifier == NO)
		cub->no_path = path;
	if (identifier == SO)
		cub->so_path = path;
	if (identifier == WE)
		cub->we_path = path;
	if (identifier == EA)
		cub->ea_path = path;
	if (identifier == S)
		cub->sp_path = path;
	set_flag(identifier, cub);
	return (SUCCESS);
}

bool	is_valid_color(char **strs)
{
	int i;

	if (check_str_num(strs) != 3)
		return (false);
	i = 0;
	while (i < 3)
	{
		if (strs[i] == NULL || !is_all_digit(strs[i])
			|| ft_strlen(strs[i]) > 4 || (ft_strlen(strs[i]) == 0))
			return (false);
		i++;
	}
	return (true);
}

int		input_color(char *line, int identifier, t_cub *cub)
{
	char	**strs;
	int		i;
	int		rgb[3];

	if (*line++ != ' ')
		return (INVALID_FORMAT);
	if (!(strs = ft_split(line, ',')))
		return (MALLOC_ERROR);
	if (!is_valid_color(strs))
		return (free_ret(strs, INVALID_FORMAT));
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(strs[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free_ret(strs, INVALID_COLOR));
		i++;
	}
	if (identifier == F)
		cub->f_color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	if (identifier == C)
		cub->c_color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	set_flag(identifier, cub);
	return (free_ret(strs, SUCCESS));
}

int		set_flag(int identifier, t_cub *cub)
{
	if (identifier == NO)
		cub->no_path_f = true;
	if (identifier == SO)
		cub->so_path_f = true;
	if (identifier == WE)
		cub->we_path_f = true;
	if (identifier == EA)
		cub->ea_path_f = true;
	if (identifier == S)
		cub->sp_path_f = true;
	if (identifier == F)
		cub->f_color_f = true;
	if (identifier == C)
		cub->c_color_f = true;
	return (ERROR);
}
