/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:46 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/24 16:03:39 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//Creates a new plane object
t_plane	*plane_create(t_vec3 point, t_vec3 normal, t_color color)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->point = point;
	plane->normal = vec3_normalize(normal);
	plane->color = color;
	return (plane);
}

//Gets the normal vector at a point on a plane
t_vec3	plane_get_normal(t_plane *plane, t_vec3 point)
{
	(void)point;
	return (plane->normal);
}

void	plane_translate(t_plane *plane, t_vec3 translation)
{
	plane->point = vec3_add(plane->point, translation);
}

//Rotates a plane by a given rotation vector
void	plane_rotate(t_plane *plane, t_vec3 rotation)
{
	plane->normal = vec3_rotate_x(plane->normal, rotation.x);
	plane->normal = vec3_rotate_y(plane->normal, rotation.y);
	plane->normal = vec3_rotate_z(plane->normal, rotation.z);
	plane->normal = vec3_normalize(plane->normal);
}
