/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:12:41 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/09 14:31:38 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	validate_cylinder_params(t_vec3 axis, double diameter,
					double height, t_color color)
{
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
	return (0);
}

int validate_plane_params(t_vec3 normal, t_color color)
{
    if (!validate_vector_normalized(normal))
    {
        normal = vec3_normalize(normal);
        if (vec3_length(normal) < EPSILON)
            return (print_error("Invalid plane normal vector\n"), -1);
    }
    if (!validate_color_values(color))
        return (print_error("Invalid plane color\n"), -1);
    return (0);
}

int validate_sphere_params(double diameter, t_color color)
{
    if (diameter <= 0)
        return (print_error("Invalid sphere diameter\n"), -1);
    if (!validate_color_values(color))
        return (print_error("Invalid sphere color\n"), -1);
    return (0);
}

/**
 * Validate that a vector is normalized (or close to being normalized)
 */
int	validate_vector_normalized(t_vec3 vector)
{
	double	length;

	// Check if vector is close to zero
	if (fabs(vector.x) < EPSILON && 
		fabs(vector.y) < EPSILON && 
		fabs(vector.z) < EPSILON)
		return (0);
	
	// Check if length is close to 1
	length = vec3_length(vector);
	if (fabs(length - 1.0) > 0.1) // Allow for some imprecision
		return (0);
	
	return (1);
}

/**
 * Validate a color's components are within the valid range (0-255)
 */
int	validate_color_values(t_color color)
{
	if (color.r < 0 || color.r > 255 ||
		color.g < 0 || color.g > 255 ||
		color.b < 0 || color.b > 255)
		return (0);
	return (1);
}
