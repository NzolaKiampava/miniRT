/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:21:04 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/29 11:41:34 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Parse a line from the scene file
 * Returns 0 on success, -1 on error
*/
int	parse_line(char **elements, t_scene *scene)
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
 * Parses a scene file and fills the scene structure
 * Returns 0 on sucess, -1 on error
*/
int	parse_scene(char *filename, t_scene *scene)
{
	int	fd;
	int	ret;

	if (!check_extension(filename, ".rt"))
		return (print_error(ERR_FORMAT), -1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error(ERR_FILE), -1);
	scene_init(scene);
	ret = process_file(fd, scene);
	if (ret == 0)
		ret = validate_scene(scene);
	return (ret);
}

/**
 * Validate the scene configuration
 	Verify camera orientation is normalized
 	Check if camera FOV is valid
 * Returns 0 on success, -1 on error
*/
int	validate_scene(t_scene *scene)
{
	if (fabs(vec3_length(scene->camera.orientation) - 1.0) > EPSILON)
		scene->camera.orientation = vec3_normalize(scene->camera.orientation);
	if (scene->camera.fov <= 0 || scene->camera.fov >= 180)
		return (print_error("Invalid camera FOV\n"), -1);
	return (0);
}
