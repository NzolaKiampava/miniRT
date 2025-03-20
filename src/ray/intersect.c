/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:00:00 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/20 10:06:52 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Ray-sphere intersection
int ray_intersect_sphere(t_ray ray, void *object, t_hit_info *hit)
{
    t_sphere *sphere = (t_sphere *)object;
    t_vec3 oc = vec3_subtract(ray.origin, sphere->center);
    double radius = sphere->diameter / 2.0;
    
    double a = vec3_dot(ray.direction, ray.direction);
    double b = 2.0 * vec3_dot(ray.direction, oc);
    double c = vec3_dot(oc, oc) - (radius * radius);
    
    double discriminant = b * b - 4 * a * c;
    printf("Sphere: a=%.2f, b=%.2f, c=%.2f, discriminant=%.2f\n", a, b, c, discriminant);
    if (discriminant < 0)
    {
        printf("No intersection: discriminant < 0\n");
        return (0);
    }
    
    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    printf("t1=%.2f, t2=%.2f\n", t1, t2);
    
    double t;
    if (t1 > EPSILON)
        t = t1;
    else if (t2 > EPSILON)
        t = t2;
    else
    {
        printf("No intersection: t values behind ray\n");
        return (0);
    }
    
    if (hit != NULL && (hit->t < 0 || t < hit->t))
    {
        hit->t = t;
        hit->point = ray_at(ray, t);
        hit->normal = vec3_normalize(vec3_subtract(hit->point, sphere->center));
        hit->color = sphere->color;
        hit->object = object;
        hit->type = OBJ_SPHERE;
        printf("Sphere hit at t=%.2f\n", t);
        return (1);
    }
    return (0);
}

// Ray-plane intersection
int ray_intersect_plane(t_ray ray, void *object, t_hit_info *hit)
{
    t_plane *plane = (t_plane *)object;
    double denom = vec3_dot(plane->normal, ray.direction);
    printf("Plane: denom=%.2f\n", denom);
    if (fabs(denom) < EPSILON)
    {
        printf("No intersection: ray parallel to plane\n");
        return (0);
    }
    
    t_vec3 p0l0 = vec3_subtract(plane->point, ray.origin);
    double t = vec3_dot(p0l0, plane->normal) / denom;
    printf("Plane: t=%.2f\n", t);
    
    if (t < EPSILON)
    {
        printf("No intersection: t < EPSILON\n");
        return (0);
    }
    
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
        printf("Plane hit at t=%.2f\n", t);
        return (1);
    }
    return (0);
}

// Ray-cylinder intersection
int ray_intersect_cylinder(t_ray ray, void *object, t_hit_info *hit)
{
	t_cylinder *cylinder;
	t_vec3 oc, v;
	double a, b, c, discriminant;
	double t, t1, t2;
	t_vec3 intersection, proj;
	double radius;

	cylinder = (t_cylinder *)object;
	oc = vec3_subtract(ray.origin, cylinder->center);
	v = vec3_normalize(cylinder->axis);
	
	// Calculate radius from diameter
	radius = cylinder->diameter / 2.0;
	
	// Vector projection of oc onto cylinder axis
	double oc_dot_v = vec3_dot(oc, v);
	t_vec3 proj_oc = vec3_multiply(v, oc_dot_v);
	
	// Vector from cylinder axis to ray origin
	t_vec3 ca = vec3_subtract(oc, proj_oc);
	
	// Vector projection of ray direction onto cylinder axis
	double ray_dot_v = vec3_dot(ray.direction, v);
	t_vec3 proj_ray = vec3_multiply(v, ray_dot_v);
	
	// Vector perpendicular to cylinder axis in direction of ray
	t_vec3 perpendicular = vec3_subtract(ray.direction, proj_ray);
	
	// Set up quadratic equation for cylinder intersection
	a = vec3_dot(perpendicular, perpendicular);
	b = 2 * vec3_dot(perpendicular, ca);
	c = vec3_dot(ca, ca) - (radius * radius);
	
	discriminant = b * b - 4 * a * c;
	printf("cylinder: a=%.2f, b=%.2f, c=%.2f, discriminant=%.2f\n", a, b, c, discriminant);
	if (discriminant < 0 || a < EPSILON)
	{	
		printf("No intersection: discriminant < 0\n");
		return (0); // No intersection
	}
	
	// Find closest intersection point
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	printf("t1=%.2f, t2=%.2f\n", t1, t2);
	
	// Get smallest positive t
	if (t1 > EPSILON)
		t = t1;
	else if (t2 > EPSILON)
		t = t2;
	else
	{	
		printf("No intersection: t values behing ray\n");
		return (0);
	}
	
	// Check if intersection is within cylinder height
	intersection = ray_at(ray, t);
	proj = vec3_subtract(intersection, cylinder->center);
	double height_proj = vec3_dot(proj, v);
	
	if (height_proj < 0 || height_proj > cylinder->height)
	{
		// Try the other intersection point
		if (t1 > EPSILON && t2 > EPSILON && t == t1)
		{
			t = t2;
			intersection = ray_at(ray, t);
			proj = vec3_subtract(intersection, cylinder->center);
			height_proj = vec3_dot(proj, v);
			
			if (height_proj < 0 || height_proj > cylinder->height)
				return (0); // Both intersections outside cylinder height
		}
		else
			return (0); // No valid intersection
	}
	
	// Update hit information
	if (hit != NULL && (hit->t < 0 || t < hit->t))
	{
		hit->t = t;
		hit->point = intersection;
		
		// Calculate normal at intersection point
		t_vec3 axis_point = vec3_add(cylinder->center, vec3_multiply(v, height_proj));
		hit->normal = vec3_normalize(vec3_subtract(hit->point, axis_point));
		
		hit->color = cylinder->color;
		hit->object = object;
		hit->type = OBJ_CYLINDER;
		printf("cylinder hit at t=%.2f\n", t);
		return (1);
	}
	
	return (0);
}

// Check intersection with any object
int ray_intersect_any(t_ray ray, void **objects, int num_objects, t_hit_info *hit)
{
    int i;
    int hit_found;
    t_hit_info temp_hit;
    t_object *obj;

    hit_found = 0;
    temp_hit.t = -1;
    
    for (i = 0; i < num_objects; i++)
    {
        obj = (t_object *)objects[i];
        printf("Checking object %d, type: %d\n", i, obj->type);
        switch (obj->type)
        {
            case OBJ_SPHERE:
                if (ray_intersect_sphere(ray, obj->data, &temp_hit))
                {
                    printf("Sphere hit at t = %.2f\n", temp_hit.t);
                    hit_found = 1;
                }
                break;
            case OBJ_PLANE:
                if (ray_intersect_plane(ray, obj->data, &temp_hit))
                {
                    printf("Plane hit at t = %.2f\n", temp_hit.t);
                    hit_found = 1;
                }
                break;
            case OBJ_CYLINDER:
                if (ray_intersect_cylinder(ray, obj->data, &temp_hit))
                {
                    printf("Cylinder hit at t = %.2f\n", temp_hit.t);
                    hit_found = 1;
                }
                break;
            default:
                printf("Unknown object type: %d\n", obj->type);
                break;
        }
    }
    
    if (hit_found && hit != NULL)
        *hit = temp_hit;
    
    return (hit_found);
}