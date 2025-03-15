/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:21:04 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/14 17:38:07 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Parse a sphere from the scene file
 * Format: sp x,y,z diameter r,g,b
 * Returns 0 on success, -1 on error
*/
int	parse_sphere(char **line, t_scene *scene)
{
	t_sphere	*sphere;
	t_object	*obj;
	t_vec3		center;
	double		diameter;
	t_color		color;

	if (count_elements(line) != 4)
		return (print_error("Invalid sphere format\n"), -1);
	
	center = parse_vector(line[1]);
	diameter = parse_double(line[2]);
	color = parse_color(line[3]);
	
	if (diameter <= 0)
		return (print_error("Invalid sphere diameter\n"), -1);
	if (!validate_color_values(color))
		return (print_error("Invalid sphere color\n"), -1);
	
	sphere = sphere_create(center, diameter, color);
	if (!sphere)
		return (print_error(ERR_MEMORY), -1);
	
	obj = object_create(OBJ_SPHERE, sphere);
	if (!obj)
	{
		free(sphere);
		return (print_error(ERR_MEMORY), -1);
	}
	
	if (ft_lstadd_back(&scene->objects, ft_lstnew(obj)) == -1)
	{
		object_free(obj);
		return (print_error(ERR_MEMORY), -1);
	}
	
	return (0);
}

/**
 * Parse a plane from the scene file
 * Format: pl x,y,z nx,ny,nz r,g,b
 * Returns 0 on success, -1 on error
*/
int	parse_plane(char **line, t_scene *scene)
{
	t_plane		*plane;
	t_object	*obj;
	t_vec3		point;
	t_vec3		normal;
	t_color		color;

	if (count_elements(line) != 4)
		return (print_error("Invalid plane format\n"), -1);
	
	point = parse_vector(line[1]);
	normal = parse_vector(line[2]);
	color = parse_color(line[3]);
	
	if (!validate_vector_normalized(normal))
	{
		normal = vec3_normalize(normal);
		if (vec3_length(normal) < EPSILON)
			return (print_error("Invalid plane normal vector\n"), -1);
	}
	
	if (!validate_color_values(color))
		return (print_error("Invalid plane color\n"), -1);
	
	plane = plane_create(point, normal, color);
	if (!plane)
		return (print_error(ERR_MEMORY), -1);
	
	obj = object_create(OBJ_PLANE, plane);
	if (!obj)
	{
		free(plane);
		return (print_error(ERR_MEMORY), -1);
	}
	
	if (ft_lstadd_back(&scene->objects, ft_lstnew(obj)) == -1)
	{
		object_free(obj);
		return (print_error(ERR_MEMORY), -1);
	}
	
	return (0);
}

/**
 * Parse a cylinder from the scene file
 * Format: cy x,y,z nx,ny,nz diameter height r,g,b
 * Returns 0 on success, -1 on error
*/
int	parse_cylinder(char **line, t_scene *scene)
{
	t_cylinder	*cylinder;
	t_object	*obj;
	t_vec3		center;
	t_vec3		axis;
	double		diameter;
	double		height;
	t_color		color;

	if (count_elements(line) != 6)
		return (print_error("Invalid cylinder format\n"), -1);
	
	center = parse_vector(line[1]);
	axis = parse_vector(line[2]);
	diameter = parse_double(line[3]);
	height = parse_double(line[4]);
	color = parse_color(line[5]);
	
	if (!validate_vector_normalized(axis))
	{
		axis = vec3_normalize(axis);
		if (vec3_length(axis) < EPSILON)
			return (print_error("Invalid cylinder axis vector\n"), -1);
	}
	
	if (diameter <= 0)
		return (print_error("Invalid cylinder diameter\n"), -1);
	if (height <= 0)
		return (print_error("Invalid cylinder height\n"), -1);
	if (!validate_color_values(color))
		return (print_error("Invalid cylinder color\n"), -1);
	
	cylinder = cylinder_create(center, axis, diameter, height, color);
	if (!cylinder)
		return (print_error(ERR_MEMORY), -1);
	
	obj = object_create(OBJ_CYLINDER, cylinder);
	if (!obj)
	{
		free(cylinder);
		return (print_error(ERR_MEMORY), -1);
	}
	
	if (ft_lstadd_back(&scene->objects, ft_lstnew(obj)) == -1)
	{
		object_free(obj);
		return (print_error(ERR_MEMORY), -1);
	}
	
	return (0);
}
