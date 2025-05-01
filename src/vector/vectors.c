/*
#include "../../includes/minirt.h"

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
	return (vec3_subtract(
			incident,
			vec3_multiply(normal, 2 * vec3_dot(normal, incident))
		));
}
bool	vec3_equals(t_vec3 v1, t_vec3 v2)
{
	return (fabs(v1.x - v2.x) < DBL_EPSILON
		&& fabs(v1.y - v2.y) < DBL_EPSILON
		&& fabs(v1.z - v2.z) < DBL_EPSILON
	);
}
bool	vec3_is_zero(t_vec3 v)
{
	return (fabs(v.x) < DBL_EPSILON
		&& fabs(v.y) < DBL_EPSILON
		&& fabs(v.z) < DBL_EPSILON
	);
}
t_vec3	vec3_clamp(t_vec3 v, double min, double max)
{
	return (vec3_create(fmax(min, fmin(max, v.x)),
			fmax(min, fmin(max, v.y)),
			fmax(min, fmin(max, v.z))
		));
}
t_vec3	vec3_rotate_x(t_vec3 v, double angle)
{
	double	rad;
	double	cos_a;
	double	sin_a;

	rad = angle * M_PI / 180.0;
	cos_a = cos(rad);
	sin_a = sin(rad);
	return (vec3_create(
			v.x,
			v.y * cos_a - v.z * sin_a,
			v.y * sin_a + v.z * cos_a
		));
}
t_vec3	vec3_rotate_y(t_vec3 v, double angle)
{
	double	rad;
	double	cos_a;
	double	sin_a;

	rad = angle * M_PI / 180.0;
	cos_a = cos(rad);
	sin_a = sin(rad);
	return (vec3_create(
			v.x * cos_a + v.z * sin_a,
			v.y,
			-v.x * sin_a + v.z * cos_a
		));
}
t_vec3	vec3_rotate_z(t_vec3 v, double angle)
{
	double		rad;
	double		cos_a;
	double		sin_a;

	rad = (angle * M_PI) / 180.0;
	cos_a = cos(rad);
	sin_a = sin(rad);
	return (vec3_create(
			v.x * cos_a - v.y * sin_a,
			v.x * sin_a + v.y * cos_a,
			v.z
		));
}
*/