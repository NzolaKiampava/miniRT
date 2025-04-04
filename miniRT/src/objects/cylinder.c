/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:50:05 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/03 12:04:49 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minirt.h"

/**
 * Creates a new cylinder object
 * @param center Center point of the cylinder
 * @param axis Direction vector of the cylinder's axis
 * @param diameter Diameter of the cylinder
 * @param height Height of the cylinder
 * @param color Color of the cylinder
 * @return Pointer to the newly created cylinder
 */
t_cylinder	*cylinder_create(t_vec3 center, t_vec3 axis, double diameter,
	double height, t_color color)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->center = center;
	cylinder->axis = vec3_normalize(axis);
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->color = color;
	return (cylinder);
}

/**
 * Gets the normal vector at a point on a cylinder
 * @param cylinder Pointer to the cylinder
 * @param point Point on the cylinder
 * @return Normal vector at the point
 */
t_vec3  cylinder_get_normal(t_cylinder *cylinder, t_vec3 point)
{
    t_vec3	center_to_point;
    t_vec3	axis_projection;
    double	projection_length;
    t_vec3	normal;


    center_to_point = vec3_subtract(point, cylinder->center);
    projection_length = vec3_dot(center_to_point, cylinder->axis);
    if (fabs(projection_length) >= cylinder->height / 2.0)
    {
        if (projection_length > 0)
            return (cylinder->axis);
        else
            return (vec3_multiply(cylinder->axis, -1.0));
    }
    axis_projection = vec3_multiply(cylinder->axis, projection_length);
    normal = vec3_subtract(center_to_point, axis_projection);
    return (vec3_normalize(normal));
}

/**
 * Translates a cylinder by a given vector
 * @param cylinder Pointer to the cylinder
 * @param translation Translation vector
 */
void	cylinder_translate(t_cylinder *cylinder, t_vec3 translation)
{
	cylinder->center = vec3_add(cylinder->center, translation);
}

/**
 * Rotates a cylinder by a given rotation vector
 * @param cylinder Pointer to the cylinder
 * @param rotation Rotation vector (in radians)
 */
void	cylinder_rotate(t_cylinder *cylinder, t_vec3 rotation)
{
	cylinder->axis = vec3_rotate_x(cylinder->axis, rotation.x);
	cylinder->axis = vec3_rotate_y(cylinder->axis, rotation.y);
	cylinder->axis = vec3_rotate_z(cylinder->axis, rotation.z);
	cylinder->axis = vec3_normalize(cylinder->axis);
}
