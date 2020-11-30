/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 10:38:03 by ynakamot          #+#    #+#             */
/*   Updated: 2020/11/30 23:13:57 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		read_cub(int fd)
{
	char	*line;
	int		rc;
	int		ret;

	line = NULL;
	while ((rc = get_next_line(fd, &line)) >= 0)
	{
		ret = perse_cub(line);
		free(line);
		if (ret != SUCCESS)
			config_error(ret);
		if (rc == 0)
			break ;
	}
	if (rc == -1)
		config_error(READ_ERROR);
	return (1);
}

int		perse_cub(char *line)
{
	char	*ptr;
	int		ret;

	ret = check_identifier(line);
	if (ret == 0)
		return (input_resolution(line + 1));
	if (ret >= 1 && ret <= 5)
		return (input_path(line + 2, ret));
	if (ret >= 6)
		return (input_color(line + 1, ret));
	if (ret == INVALID)
		is_validmap(line);
	return (ERROR);
}

int		check_identifier(char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (R);
	if (line[0] == 'N' && line[1] == 'O')
		return (NO);
	if (line[0] == 'S' && line[1] == 'O')
		return (SO);
	if (line[0] == 'W' && line[1] == 'E')
		return (WE);
	if (line[0] == 'E' && line[1] == 'A')
		return (EA);
	if (line[0] == 'S' && line[1] == ' ')
		return (S);
	if (line[0] == 'F' && line[1] == ' ')
		return (F);
	if (line[0] == 'C' && line[1] == ' ')
		return (C);
	return (INVALID);
}

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
