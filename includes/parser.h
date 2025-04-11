/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:19:15 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/09 13:14:55 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scene.h"

// Main parsing function
int parse_scene(char *filename, t_scene *scene);

// Element parsing function
int parse_ambient(char **line, t_scene *scene);
int parse_camera(char **line, t_scene *scene);
int parse_light(char **line, t_scene *scene);
int parse_sphere(char **line, t_scene *scene);
int parse_plane(char **line, t_scene *scene);
int parse_cylinder(char **line, t_scene *scene);

// Helper parsing function
t_vec3  parse_vector(char *str);
t_color parse_color(char *str);
double  parse_double(char *str);
char    **split_line(char *line);
void    free_split(char **split);
int     count_elements(char **split);

// Validation functions
int validate_scene(t_scene *scene);
int validate_vector(t_vec3 vector, double min, double max);
int validate_color(t_color color);
int validate_ratio(double ratio);
int validate_fov(double fov);
int	validate_color_values(t_color color);
int	validate_vector_normalized(t_vec3 vector);
int	add_object_to_scene(t_scene *scene, t_object *obj);
int	create_add_cylinder(t_scene *scene, t_vec3 center, t_vec3 axis,
				double diameter, double height, t_color color);

// Validates Params objects
int	validate_cylinder_params(t_vec3 axis, double diameter,
					double height, t_color color);
int validate_plane_params(t_vec3 normal, t_color color);
int validate_sphere_params(double diameter, t_color color);

#endif