/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:27:02 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:27:31 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Vector transformations
t_vec3	vec3_rotate_x(t_vec3 v, double angle)
{
	double	rad = angle * M_PI / 180.0;
	double	cos_a = cos(rad);
	double	sin_a = sin(rad);
	return (vec3_create(
		v.x,
		v.y * cos_a - v.z * sin_a,
		v.y * sin_a + v.z * cos_a
	));
}

t_vec3	vec3_rotate_y(t_vec3 v, double angle)
{
	double	rad = angle * M_PI / 180.0;
	double	cos_a = cos(rad);
	double	sin_a = sin(rad);
	return (vec3_create(
		v.x * cos_a + v.z * sin_a,
		v.y,
		-v.x * sin_a + v.z * cos_a
	));
}

t_vec3	vec3_rotate_z(t_vec3 v, double angle)
{
	double	rad = angle * M_PI / 180.0;
	double	cos_a = cos(rad);
	double	sin_a = sin(rad);
	return (vec3_create(
		v.x * cos_a - v.y * sin_a,
		v.x * sin_a + v.y * cos_a,
		v.z
	));
}