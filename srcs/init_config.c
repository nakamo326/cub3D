/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 10:38:03 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/01 00:04:17 by ynakamot         ###   ########.fr       */
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
