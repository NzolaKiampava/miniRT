/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:00:00 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/24 15:19:33 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Ray-sphere intersection
int	ray_intersect_sphere(t_ray ray, void *object, t_hit_info *hit)
{
	t_sphere	*sphere;
	t_vec3		oc;
	double		discriminant;
	double		t;

	sphere = (t_sphere *)object;
	oc = vec3_subtract(ray.origin, sphere->center);
	discriminant = calculate_sphere_discriminant(ray, sphere, oc);
	if (discriminant < 0)
		return (0);
	t = get_valid_intersection_t(discriminant, vec3_dot(ray.direction,
				ray.direction), 2.0 * vec3_dot(ray.direction, oc));
	if (t < 0)
		return (0);
	if (hit != NULL && (hit->t < 0 || t < hit->t))
	{
		fill_hit_info(hit, ray, t, sphere);
		hit->object = object;
		hit->type = OBJ_SPHERE;
		return (1);
	}
	return (0);
}

// Ray-plane intersection
int	ray_intersect_plane(t_ray ray, void *object, t_hit_info *hit)
{
	double	t;
	t_plane	*plane;

	plane = (t_plane *)object;
	if (fabs(vec3_dot(plane->normal, ray.direction)) < EPSILON)
		return (0);
	t = vec3_dot(vec3_subtract(plane->point, ray.origin),
			plane->normal) / vec3_dot(plane->normal, ray.direction);
	if (t < EPSILON)
		return (0);
	if (hit != NULL && (hit->t < 0 || t < hit->t))
	{
		hit->t = t;
		hit->point = ray_at(ray, t);
		if (vec3_dot(ray.direction, plane->normal) > 0)
			hit->normal = vec3_multiply(plane->normal, -1);
		else
			hit->normal = plane->normal;
		hit->color = plane->color;
		hit->object = object;
		hit->type = OBJ_PLANE;
		return (1);
	}
	return (0);
}

// Ray-cylinder intersection
static int	update_cylinder_hit_info(t_ray ray, t_cylinder *cylinder,
	double t, t_hit_info *hit)
{
	t_vec3	intersection;
	t_vec3	proj;
	t_vec3	v;
	t_vec3	axis_point;
	double	height_proj;

	if (hit == NULL || (hit->t >= 0 && t >= hit->t))
		return (0);
	intersection = ray_at(ray, t);
	v = vec3_normalize(cylinder->axis);
	proj = vec3_subtract(intersection, cylinder->center);
	height_proj = vec3_dot(proj, v);
	hit->t = t;
	hit->point = intersection;
	axis_point = vec3_add(cylinder->center, vec3_multiply(v, height_proj));
	hit->normal = vec3_normalize(vec3_subtract(hit->point, axis_point));
	hit->color = cylinder->color;
	hit->object = (void *)cylinder;
	hit->type = OBJ_CYLINDER;
	return (1);
}

int	ray_intersect_cylinder(t_ray ray, void *object, t_hit_info *hit)
{
	t_cylinder	*cylinder;
	double		t;

	cylinder = (t_cylinder *)object;
	t = calculate_cylinder_intersection(ray, cylinder);
	if (t < 0)
		return (0);
	return (update_cylinder_hit_info(ray, cylinder, t, hit));
}

int	ray_intersect_any(t_ray ray, void **objects,
	int num_objects, t_hit_info *hit)
{
	t_hit_info	closest_hit;
	t_object	*obj;
	int			i;
	int			hit_found;

	hit_found = 0;
	closest_hit.t = -1;
	i = 0;
	while (i < num_objects)
	{
		obj = (t_object *)objects[i];
		if (process_object_intersection(ray, obj, &closest_hit))
			hit_found = 1;
		i++;
	}
	if (hit_found && hit != NULL)
		*hit = closest_hit;
	return (hit_found);
}
