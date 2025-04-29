/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:28:57 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/29 11:42:53 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static char	*read_line(int fd)
{
	char	buffer[4096];
	char	*line;
	int		i;
	int		bytesread;

	i = 0;
	bytesread = read(fd, &buffer[i], 1);
	if (bytesread <= 0)
		return (NULL);
	while (bytesread > 0 && buffer[i] != '\n')
	{
		i++;
		if (i >= 4095)
			break ;
		bytesread = read(fd, &buffer[i], 1);
	}
	buffer[i] = '\0';
	line = ft_strdup(buffer);
	return (line);
}

int	process_line(char *line, t_scene *scene)
{
	char	**elements;
	int		ret;

	ret = 0;
	if (line[0] == '\0' || line[0] == '#')
		return (0);
	elements = split_line(line);
	if (!elements)
		return (-1);
	ret = parse_line(elements, scene);
	free_split(elements);
	return (ret);
}

int	process_file(int fd, t_scene *scene)
{
	char	*line;
	int		ret;

	ret = 0;
	line = read_line(fd);
	while (ret == 0 && line != NULL)
	{
		ret = process_line(line, scene);
		free(line);
		if (ret == 0)
			line = read_line(fd);
		else
			line = NULL;
	}
	close(fd);
	return (ret);
}
