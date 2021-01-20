/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:40:17 by ynakamot          #+#    #+#             */
/*   Updated: 2021/01/20 10:07:05 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_validmapline(char *line, t_cub *cub)
{
	int			i;
	const char	*mapchar = "012NSEW ";

	i = 0;
	while (line[i])
		if (!ft_strchr(mapchar, line[i++]))
			return (INVALID_FORMAT);
	i = cub->map_maxrow;
	if (i == MAP_BUF_SIZE)
		return (MAP_TOO_BIG);
	if (!(cub->map[i] = ft_strdup(line)))
		return (MALLOC_ERROR);
	cub->map[i + 1] = NULL;
	cub->map_maxrow++;
	if ((int)ft_strlen(line) > cub->map_maxcol)
		cub->map_maxcol = ft_strlen(line);
	return (MAP);
}

int		perse_map(int fd, t_cub *cub)
{
	int		rc;
	int		ret;
	char	*line;

	ret = 0;
	line = NULL;
	while ((rc = get_next_line(fd, &line)) >= 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ;
		}
		ret = is_validmapline(line, cub);
		free(line);
		if (ret != MAP)
			config_error(ret);
		if (rc == 0)
			break ;
	}
	if (rc == -1)
		config_error(READ_ERROR);
	return (SUCCESS);
}
