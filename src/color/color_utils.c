/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:17:46 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:18:13 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Color creation
t_color color_create(int r, int g, int b)
{
    t_color color;

    color.r = r;
    color.g = g;
    color.b = b;
    return (color);
}

// Basic color operations
t_color color_add(t_color c1, t_color c2)
{
    t_color result;

    result.r = c1.r + c2.r;
    result.g = c1.g + c2.g;
    result.b = c1.b + c2.b;
    return (color_clamp(result));
}

t_color color_multiply(t_color c, double scalar)
{
    t_color result;

    result.r = (int)(c.r * scalar);
    result.g = (int)(c.g * scalar);
    result.b = (int)(c.b * scalar);
    return (color_clamp(result));
}

t_color color_multiply_colors(t_color c1, t_color c2)
{
    t_color result;

    result.r = (c1.r * c2.r) / 255;
    result.g = (c1.g * c2.g) / 255;
    result.b = (c1.b * c2.b) / 255;
    return (result);
}

// Color conversion
int color_to_int(t_color c)
{
    // Convert RGB components to a single integer (0xRRGGBB format)
    return ((c.r & 0xFF) << 16) | ((c.g & 0xFF) << 8) | (c.b & 0xFF);
}
