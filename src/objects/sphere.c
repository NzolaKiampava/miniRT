/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:32 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/24 16:04:25 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_sphere	*sphere_create(t_vec3 center, double diameter, t_color color)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = center;
	sphere->diameter = diameter;
	sphere->color = color;
	return (sphere);
}

//Gets the normal vector at a point on a sphere
t_vec3	sphere_get_normal(t_sphere *sphere, t_vec3 point)
{
	t_vec3	normal;

	normal = vec3_subtract(point, sphere->center);
	return (vec3_normalize(normal));
}

//Translates a sphere by a given vector
void	sphere_translate(t_sphere *sphere, t_vec3 translation)
{
	sphere->center = vec3_add(sphere->center, translation);
}

// Rotating a sphere doesn't change its appearance
void	sphere_rotate(t_sphere *sphere, t_vec3 rotation)
{
	(void)sphere;
	(void)rotation;
}
