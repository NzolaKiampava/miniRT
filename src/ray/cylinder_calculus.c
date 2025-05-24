/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_calculus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:28:48 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/24 15:26:56 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	compute_discriminant(t_ray ray, t_cylinder *cyl, t_cylinder_calc *calc)
{
	t_vec3	oc;
	t_vec3	axis;
	t_vec3	proj_oc;
	t_vec3	proj_ray;
	double	ray_dot_v;

	oc = vec3_subtract(ray.origin, cyl->center);
	axis = vec3_normalize(cyl->axis);
	proj_oc = vec3_multiply(axis, vec3_dot(oc, axis));
	calc->ca = vec3_subtract(oc, proj_oc);
	ray_dot_v = vec3_dot(ray.direction, axis);
	proj_ray = vec3_multiply(axis, ray_dot_v);
	calc->perp = vec3_subtract(ray.direction, proj_ray);
	calc->b = 2 * vec3_dot(calc->perp, calc->ca);
	calc->c = vec3_dot(calc->ca, calc->ca) - pow(cyl->diameter / 2.0, 2);
	return (calc->b * calc->b - 4 * vec3_dot(calc->perp, calc->perp) * calc->c);
}

int	check_cylinder_height(t_ray ray, t_cylinder *cyl, double t)
{
	t_vec3	intersection;
	t_vec3	proj;
	double	height_proj;

	intersection = ray_at(ray, t);
	proj = vec3_subtract(intersection, cyl->center);
	height_proj = vec3_dot(proj, vec3_normalize(cyl->axis));
	return (height_proj >= 0 && height_proj <= cyl->height);
}

static double	solve_cylinder_quadratic(t_ray ray, t_cylinder *cylinder,
						t_cylinder_calc *calc, double *out_t)
{
	double	discriminant;
	double	denominator;
	double	t1;
	double	t2;

	discriminant = compute_discriminant(ray, cylinder, calc);
	denominator = 2.0 * vec3_dot(calc->perp, calc->perp);
	if (discriminant < 0 || denominator < EPSILON)
		return (-1.0);
	t1 = (-calc->b - sqrt(discriminant)) / denominator;
	t2 = (-calc->b + sqrt(discriminant)) / denominator;
	if (t1 > EPSILON)
		*out_t = t1;
	else if (t2 > EPSILON)
		*out_t = t2;
	else
		return (-1.0);
	if (t1 < t2)
		return (t1);
	else
		return (t2);
}

double	calculate_cylinder_intersection(t_ray ray, t_cylinder *cylinder)
{
	double			t;
	double			t1;
	double			t2;
	t_cylinder_calc	calc;

	t1 = solve_cylinder_quadratic(ray, cylinder, &calc, &t);
	if (t1 < 0)
		return (-1.0);
	if (t == t1)
		t2 = (-calc.b + sqrt(compute_discriminant(ray, cylinder, &calc)))
			/ (2.0 * vec3_dot(calc.perp, calc.perp));
	else if (t != t1)
		t2 = t1;
	if (check_cylinder_height(ray, cylinder, t))
		return (t);
	if (t1 > EPSILON && t2 > EPSILON && t == t1)
	{
		t = t2;
		if (check_cylinder_height(ray, cylinder, t))
			return (t);
	}
	return (-1.0);
}
