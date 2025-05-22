/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:09:39 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/22 16:42:17 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Rotate camera orientation vector
void	scene_rotate_camera(t_scene *scene, t_vec3 rotation)
{
	scene->camera.orientation = vec3_rotate_x(scene->camera.orientation,
			rotation.x);
	scene->camera.orientation = vec3_rotate_y(scene->camera.orientation,
			rotation.y);
	scene->camera.orientation = vec3_rotate_z(scene->camera.orientation,
			rotation.z);
}

// Translate camera position
void	scene_translate_camera(t_scene *scene, t_vec3 translation)
{
	scene->camera.position = vec3_add(scene->camera.position, translation);
}

// Create shadow ray slightly offset from surface to avoid self-intersection
// Check for intersection with any object
	// If intersection exists and is closer than the light source
int	scene_is_in_shadow(t_scene *scene, t_vec3 point, t_vec3 light_dir,
			double light_distance)
{
	t_ray		shadow_ray;
	t_hit_info	shadow_hit;

	shadow_ray.origin = vec3_add(point, vec3_multiply(light_dir, EPSILON));
	shadow_ray.direction = light_dir;
	if (ray_intersect_any(shadow_ray, (void **)scene->objects,
			scene->num_objects, &shadow_hit))
	{
		if (shadow_hit.t < light_distance)
			return (1);
	}
	return (0);
}
