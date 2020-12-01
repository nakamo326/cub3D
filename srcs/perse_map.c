/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakamot <ynakamot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 22:40:17 by ynakamot          #+#    #+#             */
/*   Updated: 2020/12/01 21:24:01 by ynakamot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//map正しいかは後でチェック
int		is_validmapline(char *line)
{
	int i;
	const char *mapchar = "012NSEW ";

	i = 0;
	while (line[i])
		if(!ft_strchr(mapchar, line[i++]))
			return (INVALID_FORMAT);
	i = 0;
	while (cub_info.map[i] != NULL)
		i++;
	if (!(cub_info.map[i] = ft_strdup(line)))
		return (MALLOC_ERROR);
	cub_info.map[i + 1] = NULL;
	return (MAP);
}

int		perse_map(int fd)
{
	int		rc;
	int		ret;
	char	*line;

	ret = 0;
	line = NULL;
	while ((rc = get_next_line(fd, &line)) >= 0)
	{
		ret = is_validmapline(line);
		free(line);
		if (ret != MAP)
			config_error(ret);
		if (rc == 0)
			break;
	}
	if (rc == -1)
		config_error(READ_ERROR);
	return (SUCCESS);
}
