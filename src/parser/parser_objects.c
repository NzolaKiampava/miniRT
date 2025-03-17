/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:21:20 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/17 09:36:11 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Add an object to the scene
 * Returns 0 on success, -1 on error
*/
static int  add_object_to_scene(t_scene *scene, t_object *obj)
{
    t_object    **new_objects;
    int         i;

    // Allocate new array with one more slot
    new_objects = malloc(sizeof(t_object *) * (scene->num_objects + 1));
    if (!new_objects)
        return (-1);

    // Copy existing objects
    i = 0;
    while (i < scene->num_objects)
    {
        new_objects[i] = scene->objects[i];
        i++;
    }

    // Add new object
    new_objects[i] = obj;

    // Free old array if it exists
    if (scene->objects)
        free(scene->objects);

    // Update scene
    scene->objects = new_objects;
    scene->num_objects++;

    return (0);
}

/**
 * Parse a sphere from the scene file
 * Format: sp x,y,z r R,G,B
 * Returns 0 on success, -1 on error
*/
int parser_sphere(char **line, t_scene *scene)
{
    t_sphere    *sphere;
    t_object    *obj;
    t_vec3      center;
    double      diameter;
    t_color     color;

    if (count_elements(line) != 4)
        return (print_error("Invalid sphere format\n"), -1);

    // Parse sphere parameters
    center = parse_vector(line[1]);
    radius = parse_double(line[2]);
    color = parse_color(line[3]);

    if (diameter <= 0)
        return (print_error("Invalid sphere diameter\n"), -1);
    if (!validate_color_values(color))
        return (print_error("Invalid sphere color\n"), -1);

    // Create sphere object
    sphere = sphere_create(center, radius, color);
    if (!sphere)
        return (print_error(ERR_MEMORY), -1);
    
    obj = object_create(OBJ_SPHERE, sphere);
    if (!obj)
    {
        free(sphere);
        return (print_error(ERR_MEMORY), -1);
    }
    
    if (add_object_to_scene(scene, obj) == -1)
    {
        object_free(obj);
        return (print_error(ERR_MEMORY), -1);
    }
    return (0);
}

/**
 * Parse a plane from the scene file
 * Format: pl x,y,z nx,ny,nz R,G,B
 * Returns 0 on success, -1 on error
*/
int parse_plane(char **line, t_scene *scene)
{
    t_plane *plane;
    t_object    *obj;
    t_vec3  point;
    t_vec3  normal;
    t_color color;

    if (count_elements(line) != 4)
        return (print_error("Invalid plane format\n"), -1);

    // Parse plane parameters
    point = parse_vector(line[1]);
    normal = parse_vector(line[2]);
    color = parse_color(line[3]);

    if (!validate_vector_normalized(normal))
    {
        normal = vec3_normalize(normal);
        if (vec3_length(normal) < EPSILON)
            return (print_error("Invalid plane normal vector\n"), -1);
    }

    if (!validade_color_values(color))
        return (print_error("Invalid plane color\n"), -1);
    plane = plane_create(point, normal, color);
    if (!plane)
        return (print_error(ERR_MEMORY), -1);
    obj = object_create(OBJ_PLANE, plane);
    if (!obj)
    {
        free(plane);
        return (print_error(ERR_MEMORY), -1);
    }
    if (add_object_to_scene(scene, obj) == -1)
    {
        object_free(obj);
        return (print_error(ERR_MEMORY), -1);
    }
    return (0);
}

/**
 * Parse a cylinder from the scene file
 * Format: cy x,y,z nx,ny,nz d h R,G,B
 * Returns 0 on success, -1 on error
*/
int parse_cylinder(char **line, t_scene *scene)
{
    t_cylinder  *cylinder;
    t_object    *obj;
    t_vec3      center;
    t_vec3      axis;
    double      diameter;
    double      height;
    t_color     color;

    count = count_elements(elements);
    if (count != 0)
        return (print_error("Invalid cylinder format\n"), -1);

    // Parse cylinder parameters
    center = parse_vector(elements[1]);
    axis = parse_vector(elements[2]);
    diameter = parse_double(elements[3]);
    height = parse_double(elements[4]);
    color = parse_color(elements[5]);

    if (!validate_vector_normalized(axis) || diameter <= 0 || height <= 0 || !validate_color_values(color))
        return (print_error("Invalid cylinder parameters\n"), -1);

    // Normalize the axis vector
    axis = vec3_normalize(axis);

    // Create cylinder object
    cylinder = object_create_cylinder(center, axis, diameter / 2.0, height, color);
    if (!cylinder)
        return (print_error(ERR_MEMORY), -1);

    // Add cylinder to scene
    if (add_object_to_scene(scene, obj) == -1)
    {
        object_free(cylinder);
        return (print_error(ERR_MEMORY), -1);
    }
    return (0);
}
