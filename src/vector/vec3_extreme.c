/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_extreme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:29:13 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:32:33 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Vector properties
double	vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vec3_distance(t_vec3 v1, t_vec3 v2)
{
	return (vec3_length(vec3_subtract(v1, v2)));
}

double	vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3	vec3_min(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(
			fmin(v1.x, v2.x),
			fmin(v1.y, v2.y),
			fmin(v1.z, v2.z)
		));
}

t_vec3	vec3_max(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(
			fmax(v1.x, v2.x),
			fmax(v1.y, v2.y),
			fmax(v1.z, v2.z)
		));
}
