/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:23:37 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/11 08:47:56 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Ray creation function
t_ray   ray_create(t_vec3 origin, t_vec3 direction)
{
    t_ray   ray;

    ray.origin = origin;
    ray.direction = vec3_normalize(direction); // Ensure direction is normalized
    return (ray);
}

// Compute point at distance t along ray
t_vec3 ray_at(t_ray ray, double t)
{
    t_vec3 point;

    point = vec3_add(ray.origin, vec3_multiply(ray.direction, t));
    return (point);
}

// Transform ray by translation
t_ray   ray_transformation(t_ray ray, t_vec3 translation)
{
    t_ray transformed;

    transformed.origin = vec3_add(ray.origin, translation);
    transformed.direction = ray.direction;  // Direction remains unchanged
    return (transformed);
}

// Generate camera ray fir a pixel
t_ray camera_ray(t_vec3 origin, t_vec3 direction, double fov, double aspect_ratio, double x, double y)
{
    t_ray ray;
    t_vec3 right, up;
    t_vec3 pixel_pos;
    double scale;

    ray.origin = origin;
    direction = vec3_normalize(direction);

    // Calculate scale based on FOV
    scale = tan((fov * M_PI / 180.0) / 2.0);

    // Calculate right and up vectors more robustly
    t_vec3 world_up = vec3_create(0, 1, 0);
    if (fabs(vec3_dot(direction, world_up)) > 0.999) // If direction is nearly parallel to world up
        right = vec3_normalize(vec3_cross(direction, vec3_create(0, 0, 1)));
    else
        right = vec3_normalize(vec3_cross(direction, world_up));

    up = vec3_normalize(vec3_cross(right, direction));

    // Convert pixel coordinates to normalized device coordinates (-1 to 1)
    double ndc_x = (2.0 * (x + 0.5) / WINDOW_WIDTH - 1.0) * aspect_ratio * scale;
    double ndc_y = (1.0 - 2.0 * (y + 0.5) / WINDOW_HEIGHT) * scale;

    // Calculate ray direction (relative to the camera's coordinate system)
    pixel_pos = vec3_add(vec3_add(vec3_multiply(right, ndc_x), vec3_multiply(up, ndc_y)), direction);

    ray.direction = vec3_normalize(pixel_pos);
    return (ray);
}