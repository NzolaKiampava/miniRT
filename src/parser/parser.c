/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:21:04 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/14 12:38:07 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static 	int parse_line(char **elements, t_scene *scene);

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

/**
 * Parses a scene file and fills the scene structure
 * Returns 0 on sucess, -1 on error
*/
int	parse_scene(char *filename, t_scene *scene)
{
	int	fd;
	char	*line;
	char	**elements;
	int		ret;

	if (!check_extension(filename, ".rt"))
		return (print_error(ERR_FORMAT), -1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error(ERR_FILE), -1);
	scene_init(scene);
	ret = 0;
	while (ret == 0 && (line = read_line(fd)) != NULL)
	{
		if (line[0] == '\0' || line[0] == '#')
		{
			free(line);
			continue ;
		}
		elements = split_line(line);
		if (!elements)
			ret = -1;
		else
		{
			ret = parse_line(elements, scene);
			free_split(elements);
		}
		free(line);
	}
	close(fd);
	if (ret == 0)
		ret = validate_scene(scene);
	return (ret);
}

/**
 * Parse a line from the scene file
 * Returns 0 on success, -1 on error
*/
static int	parse_line(char **elements, t_scene *scene)
{
	if (!elements[0])
		return (0);
	if (ft_strcmp(elements[0], "A") == 0)
		return (parse_ambient(elements, scene));
	else if (ft_strcmp(elements[0], "C") == 0)
		return (parse_camera(elements, scene));
	else if (ft_strcmp(elements[0], "L") == 0)
		return (parse_light(elements, scene));
	else if (ft_strcmp(elements[0], "sp") == 0)
		return (parse_sphere(elements, scene));
	else if (ft_strcmp(elements[0], "pl") == 0)
		return (parse_plane(elements, scene));
	else if (ft_strcmp(elements[0], "cy") == 0)
		return (parse_cylinder(elements, scene));
	else
		return (print_error("Unknown element type\n"), -1);
}

/**
 * Split a line into elements
 * Returns a NULL-terminated array of strings, or NULL on error
*/
char	**split_line(char *line)
{
	char	**elements;
	int		i;
	int		start;
	int		count;

	elements = (char **)malloc(sizeof(char *) * (ft_strlen(line) + 1));
	if (!elements)
		return (print_error(ERR_MEMORY), NULL);
	i = 0;
	count = 0;
	while (line[i])
	{
		// Skip whitespace
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i])
			break;
		// Mark end of element
		start = i;
		// Find end of element
		while (line[i] && line[i] != ' ' && line[i] != '\t')
			i++;
		// Copy element
		elements[count] = ft_substr(line, start, i - start);
		if (!elements[count])
		{
			free_split(elements);
			return (print_error(ERR_MEMORY), NULL);
		}
		count++;
	}
	elements[count] = NULL;
	return (elements);
}

/**
 * Count the number of elements in a NULL-terminated array
*/
int	count_elements(char **elements)
{
	int	count;

	count = 0;
	while (elements[count])
		count++;
	return (count);
}

/**
 * Free a NULL-terminated array of strings
*/
void	free_split(char **split)
{
	int	i;
	
	i = 0;
	while (split[i])
	{
		if(split[i])
			i++;
	}
	free(split);
}

/**
 * Validate the scene configuration
 * Returns 0 on success, -1 on error
*/
int	validate_scene(t_scene *scene)
{
	// Verify camera orientation is normalized
	if (fabs(vec3_length(scene->camera.orientation) - 1.0) > EPSILON)
		scene->camera.orientation = vec3_normalize(scene->camera.orientation);

	// Check if camera FOV is valid
	if (scene->camera.fov <= 0 || scene->camera.fov >= 180)
		return (print_error("Invalid camera FOV\n"), -1);

	return (0);
}