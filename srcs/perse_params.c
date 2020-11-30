/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:57:40 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/01 00:03:38 by ynakamot         ###   ########.fr       */
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
	return (SUCCESS);
}

int		input_path(char *line, int ret)
{
	char	*path;
	char	*buf;
	int		fd;
	int		rc;

	if (!(path = ft_strtrim(line, " ")))
		return (MALLOC_ERROR);
	fd = open(path, O_RDONLY);
	if ((rc = read(fd, buf, 0)) == -1)
	{
		close(fd);
		return (INVALID_FILEPATH);
	}
	close(fd);
	if (ret == NO)
		cub_info.no_path = path;
	if (ret == SO)
		cub_info.so_path = path;
	if (ret == WE)
		cub_info.we_path = path;
	if (ret == EA)
		cub_info.ea_path = path;
	if (ret == S)
		cub_info.sp_path = path;
	return (SUCCESS);
}

int		input_color(char *line, int ret)
{
	char	**strs;
	int		i;
	int		rgb[3];

	while (ft_isspace(*line))
		line++;
	if (!(strs = ft_split(line, ',')))
		return (MALLOC_ERROR);
	i = 0;
	while (i < 3)
	{
		if (strs[i] == NULL)
			return (INVALID_FORMAT);
		rgb[i] = ft_atoi(strs[i]);
		if (rgb[i] < 0 || rgb[i++] > 255)
			return (INVALID_COLOR);
		if (ret == F)
			cub_info.f_color[i] = rgb[i++];
		if (ret == C)
			cub_info.c_color[i] = rgb[i++];
	}
	return (SUCCESS);
}
