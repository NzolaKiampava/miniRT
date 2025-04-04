/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:16:07 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:16:24 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Predefined colors
t_color color_black(void)
{
    return (color_create(0, 0, 0));
}

t_color color_white(void)
{
    return (color_create(255, 255, 255));
}

t_color color_red(void)
{
    return (color_create(255, 0, 0));
}

t_color color_green(void)
{
    return (color_create(0, 255, 0));
}

t_color color_blue(void)
{
    return (color_create(0, 0, 255));
}