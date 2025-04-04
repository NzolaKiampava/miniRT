/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:22:23 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:33:12 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Vector creation and basic operations
t_vec3	vec3_create(double x, double y, double z)
{
	t_vec3	v;
	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec3_reflect(t_vec3 incident, t_vec3 normal)
{
	// R = I - 2(N · I)N
	return (vec3_subtract(
		incident, 
		vec3_multiply(normal, 2 * vec3_dot(normal, incident))
	));
}

bool	vec3_equals(t_vec3 v1, t_vec3 v2)
{
	return (
		fabs(v1.x - v2.x) < DBL_EPSILON &&
		fabs(v1.y - v2.y) < DBL_EPSILON &&
		fabs(v1.z - v2.z) < DBL_EPSILON
	);
}

bool	vec3_is_zero(t_vec3 v)
{
	return (
		fabs(v.x) < DBL_EPSILON &&
		fabs(v.y) < DBL_EPSILON &&
		fabs(v.z) < DBL_EPSILON
	);
}

t_vec3	vec3_clamp(t_vec3 v, double min, double max)
{
	return (vec3_create(
		fmax(min, fmin(max, v.x)),
		fmax(min, fmin(max, v.y)),
		fmax(min, fmin(max, v.z))
	));
}
