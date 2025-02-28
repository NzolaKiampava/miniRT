/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:19:44 by nkiampav          #+#    #+#             */
/*   Updated: 2025/02/27 09:19:46 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "color.h"

typedef struct s_ray
{
    t_vec3  origin;
    t_vec3  direction;
}   t_ray;

typedef struct  s_hit_info
{
    t_vec3  point;                   // Intersection point
    t_vec3  normal;                  // Surface normal at intersection
    double  t;                       // Distance along ray
    t_color color;                   // Object color
    void    *object;                 // Pointer to hit object
    int     type;                    // Type of the hit object
}   t_hit_info;


// Ray functions
t_ray ray_create(t_vec3 origin, t_vec3 direction);
t_vec3 ray_at(t_ray ray, double t);
t_ray   ray_transformation(t_ray ray, t_vec3 translation);

// Ray object intersection function
int ray_intersect_sphere(t_ray ray, void *sphere, t_hit_info *hit);
int ray_intersect_plane(t_ray ray, void *plane, t_hit_info *hit);
int ray_intersect_cylinder(t_ray ray, void *cylinder, t_hit_info *hit);
int ray_intersect_any(t_ray ray, void **object, int num_objects, t_hit_info *hit);

t_ray   camera_ray(t_vec3 origin, t_vec3 directoin, double fov, double aspect_ratio, double x, double y);

#endif