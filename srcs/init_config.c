/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 10:38:03 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/01 15:35:27 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		read_cub(int fd)
{
	char	*line;
	int		rc;
	int		ret;

	ret = 0;
	line = NULL;
	while ((rc = get_next_line(fd, &line)) >= 0 && ret != MAP)
	{
		if (rc == 0)
			config_error(NO_MAP_INFILE);
		ret = perse_line(line);
		free(line);
		if (ret != SUCCESS && ret != MAP)
			config_error(ret);
	}
	while ((rc = get_next_line(fd, &line)) > 0)
	{
		ret = is_validmapline(line);
		free(line);
		if (ret != SUCCESS)
			config_error(ret);
	}
	if (rc == -1)
		config_error(READ_ERROR);
	return (SUCCESS);
}
//mapにはいったらidentifierこないはず。
//map確認する段階に入ったらidentifier来たらエラー
//map正しいかは後でチェック

int		perse_line(char *line)
{
	char	*ptr;
	int		ret;

	if (*line == '\0')
		return (SUCCESS);
	ret = check_identifier(line);
	if(check_multiple(ret) == ERROR)
		return (MULTIPLE_ID);
	if (ret == R)
		return (input_resolution(line + 1));
	if (ret >= NO && ret <= S)
		return (input_path(line + 2, ret));
	if (ret >= F)
		return (input_color(line + 1, ret));
	if (ret == MAP)
		return (is_validmapline(line));
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
	return (MAP);
}

int		check_multiple(int identifier)
{
	if (identifier == R && cub_info.win_f == true)
		return (ERROR);
	if (identifier == NO && cub_info.no_path_f == true)
		return (ERROR);
	if (identifier == SO && cub_info.so_path_f == true)
		return (ERROR);
	if (identifier == WE && cub_info.we_path_f == true)
		return (ERROR);
	if (identifier == EA && cub_info.ea_path_f == true)
		return (ERROR);
	if (identifier == S && cub_info.sp_path_f == true)
		return (ERROR);
	if (identifier == F && cub_info.f_color_f == true)
		return (ERROR);
	if (identifier == C && cub_info.c_color_f == true)
		return (ERROR);
	return (SUCCESS);
}