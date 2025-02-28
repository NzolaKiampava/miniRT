/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:20:21 by nkiampav          #+#    #+#             */
/*   Updated: 2025/02/27 09:20:24 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct  s_color
{
    int r;
    int g;
    int b;
}   t_color;

// Color creation and basic operations
t_color color_create(int r, int g, int b);
t_color color_add(t_color c1, t_color c2);
t_color color_multiply(t_color c, double scolar);
t_color color_multiply_colors(t_color c1, t_color c2);

// Color conversion
int color_to_int(t_color c);
t_color int_to_color(int rgb);

// Color utilities
t_color color_clamp(t_color c);
t_color color_lerp(t_color c1, t_color c2, double t);
t_color color_parse(char *str);

// Predefined colors
t_color color_black(void);
t_color color_white(void);
t_color color_red(void);
t_color color_green(void);
t_color color_blue(void);

#endif