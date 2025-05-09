/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:15:48 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/09 08:25:09 by nkiampav         ###   ########.fr       */
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
	printf("H           : T.betw. height and diam. resize for cylinders\n");
	printf("Arrow keys  : Move or rotate selected object\n");
	printf("+ / -       : Resize selected object\n");
	printf("=====================\n\n");
}

/**
 * Displays information about the currently selected object
 * @param scene Scene pointer
 */
void	display_sphere_info(t_sphere *sphere)
{
	printf("Type: Sphere\n");
	printf("Center: (%.2f, %.2f, %.2f)\n",
		sphere->center.x, sphere->center.y, sphere->center.z);
	printf("Diameter: %.2f\n", sphere->diameter);
}

void	display_plane_info(t_plane *plane)
{
	printf("Type: Plane\n");
	printf("Point: (%.2f, %.2f, %.2f)\n",
		plane->point.x, plane->point.y, plane->point.z);
	printf("Normal: (%.2f, %.2f, %.2f)\n",
		plane->normal.x, plane->normal.y, plane->normal.z);
}

void	display_cylinder_info(t_cylinder *cylinder)
{
	printf("Type: Cylinder\n");
	printf("Center: (%.2f, %.2f, %.2f)\n",
		cylinder->center.x, cylinder->center.y, cylinder->center.z);
	printf("Axis: (%.2f, %.2f, %.2f)\n",
		cylinder->axis.x, cylinder->axis.y, cylinder->axis.z);
	printf("Diameter: %.2f\n", cylinder->diameter);
	printf("Height: %.2f\n", cylinder->height);
}

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
		display_sphere_info((t_sphere *)obj->data);
	else if (obj->type == OBJ_PLANE)
		display_plane_info((t_plane *)obj->data);
	else if (obj->type == OBJ_CYLINDER)
		display_cylinder_info((t_cylinder *)obj->data);
	if (scene->rotation_mode)
		printf("MOde: Rotation\n");
	else
		printf("Mode: Translation\n");
}
