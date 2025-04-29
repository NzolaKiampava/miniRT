/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:23:04 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:32:20 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Utility functions
void	vec3_print(t_vec3 v)
{
	printf("Vec3: (%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}

t_vec3	vec3_normalize(t_vec3 v)
{
	double	length;

	length = vec3_length(v);
	if (length == 0)
		return (vec3_create(0, 0, 0));
	return (vec3_divide(v, length));
}

bool	vec3_is_normalized(t_vec3 v)
{
	return (fabs(vec3_length(v) - 1.0) < DBL_EPSILON);
}

// Vector operations
double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		));
}
