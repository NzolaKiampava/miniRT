/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_optns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:25:53 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:26:26 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec3	vec3_subtract(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vec3	vec3_multiply(t_vec3 v, double scalar)
{
	return (vec3_create(v.x * scalar, v.y * scalar, v.z * scalar));
}

t_vec3	vec3_divide(t_vec3 v, double scalar)
{
	if (scalar == 0)
	{
		return (vec3_create(0, 0, 0));
	}
	return (vec3_create(v.x / scalar, v.y / scalar, v.z / scalar));
}

t_vec3	vec3_negate(t_vec3 v)
{
	return (vec3_create(-v.x, -v.y, -v.z));
}
