/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:21:46 by maalmeid          #+#    #+#             */
/*   Updated: 2025/05/24 11:47:14 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Check intersection with a single object based on its type
int	ray_intersect_object(t_ray ray, t_object *obj, t_hit_info *temp_hit)
{
	if (!obj->type)
		return (0);
	if (obj->type == OBJ_SPHERE)
		return (ray_intersect_sphere(ray, obj->data, temp_hit));
	else if (obj->type == OBJ_PLANE)
		return (ray_intersect_plane(ray, obj->data, temp_hit));
	else if (obj->type == OBJ_CYLINDER)
		return (ray_intersect_cylinder(ray, obj->data, temp_hit));
	return (0);
}

// Process intersection with a single object and update hit info if closer
int	process_object_intersection(t_ray ray, t_object *obj,
		t_hit_info *closest_hit)
{
	t_hit_info	temp_hit;

	temp_hit.t = -1;
	if (ray_intersect_object(ray, obj, &temp_hit))
	{
		if (closest_hit->t < 0 || (temp_hit.t > 0
				&& temp_hit.t < closest_hit->t))
		{
			*closest_hit = temp_hit;
			return (1);
		}
	}
	return (0);
}

double	calculate_sphere_discriminant(t_ray ray, t_sphere *sphere, t_vec3 oc)
{
	double	radius;
	double	a;
	double	b;
	double	c;

	radius = sphere->diameter / 2.0;
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(ray.direction, oc);
	c = vec3_dot(oc, oc) - (radius * radius);
	return (b * b - 4 * a * c);
}

double	get_valid_intersection_t(double discriminant, double a, double b)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > EPSILON)
		return (t1);
	else if (t2 > EPSILON)
		return (t2);
	return (-1);
}

void	fill_hit_info(t_hit_info *hit, t_ray ray, double t, t_sphere *sphere)
{
	hit->t = t;
	hit->point = ray_at(ray, t);
	hit->normal = vec3_normalize(vec3_subtract(hit->point, sphere->center));
	hit->color = sphere->color;
}
