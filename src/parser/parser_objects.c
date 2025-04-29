/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:21:20 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/29 11:00:12 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Parse a sphere from the scene file
 * Format: sp x,y,z r R,G,B
 * Returns 0 on success, -1 on error
*/
static int	create_and_add_sphere(t_scene *scene, t_vec3 center,
					double diameter, t_color color)
{
	t_sphere	*sphere;
	t_object	*obj;

	sphere = sphere_create(center, diameter, color);
	if (!sphere)
		return (print_error(ERR_MEMORY), -1);
	obj = object_create(OBJ_SPHERE, sphere);
	if (!obj)
	{
		free(sphere);
		return (print_error(ERR_MEMORY), -1);
	}
	if (add_object_to_scene(scene, obj) == -1)
	{
		object_free(obj);
		return (print_error(ERR_MEMORY), -1);
	}
	return (0);
}

int	parse_sphere(char **line, t_scene *scene)
{
	t_vec3	center;
	double	diameter;
	t_color	color;

	if (count_elements(line) != 4)
		return (print_error("Invalid sphere format\n"), -1);
	center = parse_vector(line[1]);
	diameter = parse_double(line[2]);
	color = parse_color(line[3]);
	if (validate_sphere_params(diameter, color) == -1)
		return (-1);
	return (create_and_add_sphere(scene, center, diameter, color));
}

/**
 * Parse a plane from the scene file
 * Format: pl x,y,z nx,ny,nz R,G,B
 * Returns 0 on success, -1 on error
*/
static int	create_and_add_plane(t_scene *scene, t_vec3 point,
					t_vec3 normal, t_color color)
{
	t_plane		*plane;
	t_object	*obj;

	plane = plane_create(point, normal, color);
	if (!plane)
		return (print_error(ERR_MEMORY), -1);
	obj = object_create(OBJ_PLANE, plane);
	if (!obj)
	{
		free(plane);
		return (print_error(ERR_MEMORY), -1);
	}
	if (add_object_to_scene(scene, obj) == -1)
	{
		object_free(obj);
		return (print_error(ERR_MEMORY), -1);
	}
	return (0);
}

int	parse_plane(char **line, t_scene *scene)
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;

	if (count_elements(line) != 4)
		return (print_error("Invalid plane format\n"), -1);
	point = parse_vector(line[1]);
	normal = parse_vector(line[2]);
	color = parse_color(line[3]);
	if (validate_plane_params(normal, color) == -1)
		return (-1);
	return (create_and_add_plane(scene, point, normal, color));
}

/**
 * Parse a cylinder from the scene file
 * Format: cy x,y,z nx,ny,nz d h R,G,B
 * Returns 0 on success, -1 on error
*/
int	parse_cylinder(char **line, t_scene *scene)
{
	t_cylinder params;

	if (count_elements(line) != 6)
		return (print_error("Invalid cylinder format\n"), -1);
	params.center = parse_vector(line[1]);
	params.axis = parse_vector(line[2]);
	params.diameter = parse_double(line[3]);
	params.height = parse_double(line[4]);
	params.color = parse_color(line[5]);
	if (validate_cylinder_params(params.axis, params.diameter, params.height, params.color) == -1)
		return (-1);
	return (create_add_cylinder(scene, params));
}
