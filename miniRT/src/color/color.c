/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:51:16 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:17:37 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color int_to_color(int rgb)
{
    t_color c;

    // Extract RGB components from integer
    c.r = (rgb >> 16) & 0xFF;
    c.g = (rgb >> 8) & 0xFF;
    c.b = rgb & 0xFF;
    return (c);
}

double  color_to_scalar(t_color c)
{
    // Convert RGB color to a scalar value (usually average of components)
    // This is commonly used in lighting used in lighting calculations
    return ((double)(c.r + c.g + c.b) / (3.0 * 255.0));
}

// Color utilities
t_color color_clamp(t_color c)
{
    t_color result;

    // Clamp RGB values to 0-255 range
    result.r = (c.r < 0) ? 0 : ((c.r > 255) ? 255 : c.r);
    result.g = (c.g < 0) ? 0 : ((c.g > 255) ? 255 : c.g);
    result.b = (c.b < 0) ? 0 : ((c.b > 255) ? 255 : c.b);
    return (result);
}

t_color color_lerp(t_color c1, t_color c2, double t)
{
    t_color result;

    // Linear interpolation between two colors
    if (t < 0)
        t = 0;
    if (t > 1)
        t = 1;
    result.r = (int)(c1.r * (1 - t) + c2.r * t);
    result.g = (int)(c1.g * (1 - t) + c2.g * t);
    result.b = (int)(c1.b * (1 - t) + c2.b * t);
    return (result);
}

// Parse color from string "r,g,b" format
t_color color_parse(char *str)
{
    t_color color;
    char    *token;
    char    *saveptr;

    color = color_black();
    if (!str)
        return (color);

    // Parse red component
    token = strtok_r(str, ",", &saveptr);
    if (token)
        color.r = ft_atoi(token);

    // Parse green component
    token = strtok_r(NULL, ",", &saveptr);
    if (token)
        color.g = ft_atoi(token);

    // Parse blue component
    token = strtok_r(NULL, ",", &saveptr);
    if (token)
        color.b = ft_atoi(token);
    
    return (color_clamp(color));
}
