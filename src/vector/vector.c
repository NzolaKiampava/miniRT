/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:22:23 by nkiampav          #+#    #+#             */
/*   Updated: 2025/02/27 09:22:25 by nkiampav         ###   ########.fr       */
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
		// Handle division by zero
		return (vec3_create(0, 0, 0));
	}
	return (vec3_create(v.x / scalar, v.y / scalar, v.z / scalar));
}

t_vec3	vec3_negate(t_vec3 v)
{
	return (vec3_create(-v.x, -v.y, -v.z));
}

// Vector properties
double	vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vec3_distance(t_vec3 v1, t_vec3 v2)
{
	return (vec3_length(vec3_subtract(v1, v2)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	double	length = vec3_length(v);
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
	return (vec3_create(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	));
}

t_vec3	vec3_reflect(t_vec3 incident, t_vec3 normal)
{
	// R = I - 2(N · I)N
	return (vec3_subtract(
		incident, 
		vec3_multiply(normal, 2 * vec3_dot(normal, incident))
	));
}

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

// Utility functions
void	vec3_print(t_vec3 v)
{
	printf("Vec3: (%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
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