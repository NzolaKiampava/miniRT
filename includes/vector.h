/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:19:31 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/13 16:29:20 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdbool.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

// Vector creation and basic operations
t_vec3	vec3_create(double x, double y, double z);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_subtract(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_multiply(t_vec3 v, double scalar);
t_vec3	vec3_divide(t_vec3 v, double scalar);
t_vec3	vec3_negate(t_vec3 v);

// Vector properties
double	vec3_length(t_vec3 v);
double	vec3_length_squared(t_vec3 v);
double	vec3_distance(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_normalize(t_vec3 v);
bool	vec3_is_normalized(t_vec3 v);

// Vector operations
double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_reflect(t_vec3 incident, t_vec3 normal);

// Vector   transformations
t_vec3	vec3_rotate_x(t_vec3 v, double angle);
t_vec3	vec3_rotate_y(t_vec3 v, double angle);
t_vec3	vec3_rotate_z(t_vec3 v, double angle);

// Utility functions
void	vec3_print(t_vec3 v);
bool	vec3_equals(t_vec3 v1, t_vec3 v2);
bool	vec3_is_zero(t_vec3 v);
t_vec3	vec3_clamp(t_vec3 v, double min, double max);
t_vec3	vec3_min(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_max(t_vec3 v1, t_vec3 v2);

#endif
