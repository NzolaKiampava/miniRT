/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:30:50 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/25 16:17:39 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Parse a vector from a string (format: x,y,z)
 */
t_vec3	parse_vector(char *str)
{
	t_vec3	vector;
	char	**parts;
	int		i;

	parts = ft_split(str, ',');
	if (!parts)
		return (vec3_create(0, 0, 0));
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
	{
		free_split(parts);
		return (vec3_create(0, 0, 0));
	}
	vector = vec3_create(
			ft_atof(parts[0]),
			ft_atof(parts[1]),
			ft_atof(parts[2])
			);
	free_split(parts);
	return (vector);
}

/**
 * Parse a color from a string (format: R,G,B)
 */
t_color	parse_color(char *str)
{
	t_color	color;
	char	**parts;
	int		i;

	parts = ft_split(str, ',');
	if (!parts)
		return (color_create(0, 0, 0));
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
	{
		free_split(parts);
		return (color_create(0, 0, 0));
	}
	color = color_create(
			ft_atoi(parts[0]),
			ft_atoi(parts[1]),
			ft_atoi(parts[2])
			);
	free_split(parts);
	return (color);
}

/**
 * Parse a double from a string
 */
double	parse_double(char *str)
{
	return (ft_atof(str));
}

/**
 * Split a line into elements
 * Returns a NULL-terminated array of strings, or NULL on error
*/

static char	**allocate_elements(char *line)
{
	char	**elements = (char **)malloc(sizeof(char *) * (ft_strlen(line) + 1));
	if (!elements)
		print_error(ERR_MEMORY);
	return (elements);
}

static char	*extract_element(char *line, int start, int end)
{
	char	*element = ft_substr(line, start, end - start);
	if (!element)
		print_error(ERR_MEMORY);
	return (element);
}

char	**split_line(char *line)
{
	char	**elements = allocate_elements(line);
	int		i = 0, start, count = 0;
	if (!elements)
		return (NULL);
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i])
			break ;
		start = i;
		while (line[i] && line[i] != ' ' && line[i] != '\t')
			i++;
		elements[count] = extract_element(line, start, i);
		if (!elements[count++])
			return (free_split(elements), NULL);
	}
	elements[count] = NULL;
	return (elements);
}
