/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:15:48 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/01 10:34:54 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * Displays help information about the available key commands
 */
void	display_help(void)
{
	printf("\n==== miniRT Controls ====\n");
	printf("ESC         : Exit program\n");
	printf("TAB         : Select next object\n");
	printf("R           : Toggle between rotation and translation mode\n");
	printf("H           : Toggle between height and diameter resize for cylinders\n");
	printf("Arrow keys  : Move or rotate selected object\n");
	printf("+ / -       : Resize selected object\n");
	printf("=====================\n\n");
}

/**
 * Displays information about the currently selected object
 * @param scene Scene pointer
 */
void	display_object_info(t_scene *scene)
{
	t_object	*obj;
	
	if (scene->num_objects == 0 || scene->selected_obj_index < 0)
	{
		printf("No object selected\n");
		return ;
	}
	
	obj = scene->objects[scene->selected_obj_index];
	printf("Selected object: %d\n", scene->selected_obj_index);
	
	if (obj->type == OBJ_SPHERE)
	{
		t_sphere *sphere = (t_sphere *)obj->data;
		printf("Type: Sphere\n");
		printf("Center: (%.2f, %.2f, %.2f)\n", 
			sphere->center.x, sphere->center.y, sphere->center.z);
		printf("Diameter: %.2f\n", sphere->diameter);
	}
	else if (obj->type == OBJ_PLANE)
	{
		t_plane *plane = (t_plane *)obj->data;
		printf("Type: Plane\n");
		printf("Point: (%.2f, %.2f, %.2f)\n", 
			plane->point.x, plane->point.y, plane->point.z);
		printf("Normal: (%.2f, %.2f, %.2f)\n", 
			plane->normal.x, plane->normal.y, plane->normal.z);
	}
	else if (obj->type == OBJ_CYLINDER)
	{
		t_cylinder *cylinder = (t_cylinder *)obj->data;
		printf("Type: Cylinder\n");
		printf("Center: (%.2f, %.2f, %.2f)\n", 
			cylinder->center.x, cylinder->center.y, cylinder->center.z);
		printf("Axis: (%.2f, %.2f, %.2f)\n", 
			cylinder->axis.x, cylinder->axis.y, cylinder->axis.z);
		printf("Diameter: %.2f\n", cylinder->diameter);
		printf("Height: %.2f\n", cylinder->height);
	}
	
	printf("Mode: %s\n", scene->rotation_mode ? "Rotation" : "Translation");
}