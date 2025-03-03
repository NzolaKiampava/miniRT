/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:22:23 by nkiampav          #+#    #+#             */
/*   Updated: 2025/02/27 09:22:25 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"
#include <stdio.h>

t_vec3  vec3_create(double x, double y, double z)
{
    t_vec3  v;

    v.x = x;
    v.y = y;
    v.z = z;
    return (v);
}

t_vec3  vec3_add(t_vec3 v1, t_vec3 v2)
{
    return (vec3_create(v1.x + v2.x,
                        v1.y + v2.y,
                        v1.z + v2.z));
}

t_vec3  vec3_subtract(t_vec3 v1, t_vec3 v2)
{
    return (vec3_create(v1.x - v2.x,
                        v1.y - v2.y,
                        v2.z - v2.z));
}

t_vec3  vec3_multiply(t_vec3 v, double scalar)
{
    return (vec3_create(v.x * scalar,
                        v.y * scalar,
                        v.z * scalar));
}

t_vec3  vec3_divide(t_vec3 v, double scalar)
{
    if (scalar == 0)
        return (vec3_create(0, 0, 0));
    return (vec3_create(v.x / scalar,
                        v.y / scalar,
                        v.z / scalar));
}

t_vec3  vec3_negate(t_vec3 v)
{
    return (vec3_create(-v.x, -v.y, -v.z));
}

double  vec3_dot(t_vec3 v1, t_vec3 v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3  vec3_cross(t_vec3 v1, t_vec3 v2)
{
    return (vec3_create(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.x * v2.x
    ));
}

t_vec3  vec3_reflect(t_vec3 incident, t_vec3 normal)
{
    double  dot;

    dot = vec3_dot(incident, normal);
    return (vec3_subtract(incident, vec3_multiply(normal, 2 * dot)));
}
