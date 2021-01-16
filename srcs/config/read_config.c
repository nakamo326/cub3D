/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 10:38:03 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/16 17:30:38 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int		check_multiple(int identifier, t_cub *cub)
{
	if (identifier == R && cub->win_f == true)
		return (ERROR);
	if (identifier == NO && cub->no_path_f == true)
		return (ERROR);
	if (identifier == SO && cub->so_path_f == true)
		return (ERROR);
	if (identifier == WE && cub->we_path_f == true)
		return (ERROR);
	if (identifier == EA && cub->ea_path_f == true)
		return (ERROR);
	if (identifier == S && cub->sp_path_f == true)
		return (ERROR);
	if (identifier == F && cub->f_color_f == true)
		return (ERROR);
	if (identifier == C && cub->c_color_f == true)
		return (ERROR);
	return (SUCCESS);
}

int		perse_line(char *line, t_cub *cub)
{
	int		ret;

	if (*line == '\0')
		return (SUCCESS);
	ret = check_identifier(line);
	if (check_multiple(ret, cub) == ERROR)
		return (MULTIPLE_ID);
	if (ret == R)
		return (input_resolution(line + 1, cub));
	if (ret >= NO && ret <= S)
		return (input_path(line + 2, ret, cub));
	if (ret == F || ret == C)
		return (input_color(line + 1, ret, cub));
	if (ret == MAP)
		return (is_validmapline(line, cub));
	return (ERROR);
}

int		read_cub(int fd, t_cub *cub)
{
	char	*line;
	int		rc;
	int		ret;

	ret = 0;
	line = NULL;
	while (ret != MAP && (rc = get_next_line(fd, &line)) >= 0)
	{
		if (rc == 0)
			config_error(NO_MAP_INFILE);
		ret = perse_line(line, cub);
		free(line);
		if (ret != SUCCESS && ret != MAP)
			config_error(ret);
	}
	if (rc == -1)
		config_error(READ_ERROR);
	return (perse_map(fd, cub));
}
