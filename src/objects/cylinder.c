/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:50:05 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/24 16:01:01 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_cylinder	*cylinder_create(t_cylinder params)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->center = params.center;
	cylinder->axis = vec3_normalize(params.axis);
	cylinder->diameter = params.diameter;
	cylinder->height = params.height;
	cylinder->color = params.color;
	return (cylinder);
}

t_vec3	cylinder_get_normal(t_cylinder *cylinder, t_vec3 point)
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

void	cylinder_translate(t_cylinder *cylinder, t_vec3 translation)
{
	cylinder->center = vec3_add(cylinder->center, translation);
}

void	cylinder_rotate(t_cylinder *cylinder, t_vec3 rotation)
{
	cylinder->axis = vec3_rotate_x(cylinder->axis, rotation.x);
	cylinder->axis = vec3_rotate_y(cylinder->axis, rotation.y);
	cylinder->axis = vec3_rotate_z(cylinder->axis, rotation.z);
	cylinder->axis = vec3_normalize(cylinder->axis);
}
