/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:16:17 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/24 16:02:55 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//Creates a new general object container
t_object	*object_create(int type, void *data)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->data = data;
	return (obj);
}

//Gets the normal vector at a point on an object
t_vec3	object_get_normal(void *obj, int type, t_vec3 point)
{
	if (type == OBJ_SPHERE)
		return (sphere_get_normal((t_sphere *)obj, point));
	else if (type == OBJ_PLANE)
		return (plane_get_normal((t_plane *)obj, point));
	else if (type == OBJ_CYLINDER)
		return (cylinder_get_normal((t_cylinder *)obj, point));
	return ((t_vec3){0, 0, 0});
}

//Gets the color of an object
t_color	object_get_color(void *obj, int type)
{
	if (type == OBJ_SPHERE)
		return (((t_sphere *)obj)->color);
	else if (type == OBJ_PLANE)
		return (((t_plane *)obj)->color);
	else if (type == OBJ_CYLINDER)
		return (((t_cylinder *)obj)->color);
	return ((t_color){0, 0, 0});
}

//Translates an object by a given vector
void	object_translate(t_object *obj, t_vec3 translation)
{
	if (!obj || !obj->data)
		return ;
	if (obj->type == OBJ_SPHERE)
		sphere_translate((t_sphere *)obj->data, translation);
	else if (obj->type == OBJ_PLANE)
		plane_translate((t_plane *)obj->data, translation);
	else if (obj->type == OBJ_CYLINDER)
		cylinder_translate((t_cylinder *)obj->data, translation);
}

// Rotates an object by a given rotation vector
void	object_rotate(t_object *obj, t_vec3 rotation)
{
	if (!obj || !obj->data)
		return ;
	if (obj->type == OBJ_SPHERE)
		sphere_rotate((t_sphere *)obj->data, rotation);
	else if (obj->type == OBJ_PLANE)
		plane_rotate((t_plane *)obj->data, rotation);
	else if (obj->type == OBJ_CYLINDER)
		cylinder_rotate((t_cylinder *)obj->data, rotation);
}
