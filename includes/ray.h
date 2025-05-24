/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:19:44 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/24 13:39:35 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "color.h"
# include "objects.h"

typedef struct s_camera_params
{
	t_vec3	origin;
	t_vec3	direction;
	double	fov;
	double	aspect_ratio;
}	t_camera_params;

typedef struct s_pixel_coords
{
	double	x;
	double	y;
}	t_pixel_coords;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_hit_calc
{
	double		t;
	void		*object;
	t_vec3		intersection;
	t_cylinder	*cyl;
}	t_hit_calc;

typedef struct s_hit_info
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
	double	t;
	void	*object;
	int		type;
}	t_hit_info;

typedef struct s_cylinder_calc
{
	t_vec3	ca;
	t_vec3	perp;
	double	b;
	double	c;
}	t_cylinder_calc;

// Ray functions
t_ray	ray_create(t_vec3 origin, t_vec3 direction);
t_vec3	ray_at(t_ray ray, double t);
t_ray	ray_transformation(t_ray ray, t_vec3 translation);

// Camera ray generation
t_ray	camera_ray(t_camera_params cam_params, t_pixel_coords pixel);

// Ray object intersection function
int		ray_intersect_sphere(t_ray ray, void *sphere, t_hit_info *hit);
int		ray_intersect_plane(t_ray ray, void *plane, t_hit_info *hit);
int		ray_intersect_cylinder(t_ray ray, void *cylinder,
			t_hit_info *hit);
int		ray_intersect_any(t_ray ray, void **object, int num_objects,
			t_hit_info *hit);

// Intersection UTILS
int		ray_intersect_object(t_ray ray, t_object *obj, t_hit_info *temp_hit);
int		process_object_intersection(t_ray ray, t_object *obj,
			t_hit_info *closest_hit);
double	calculate_sphere_discriminant(t_ray ray, t_sphere *sphere, t_vec3 oc);
double	get_valid_intersection_t(double discriminant, double a, double b);
void	fill_hit_info(t_hit_info *hit, t_ray ray, double t, t_sphere *sphere);

// Cylinder utils
double	compute_discriminant(t_ray ray, t_cylinder *cyl, t_cylinder_calc *calc);
int		check_cylinder_height(t_ray ray, t_cylinder *cyl, double t);
double	calculate_cylinder_intersection(t_ray ray, t_cylinder *cylinder);

#endif
