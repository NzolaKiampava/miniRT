/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:39:49 by nkiampav          #+#    #+#             */
/*   Updated: 2025/05/22 08:40:15 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		print_error("Failed to initialize MiniLibX\n");
	scene->win = mlx_new_window(scene->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "miniRT");
	if (!scene->win)
		print_error("Failed to create window\n");
}

void	my_mlx_pixel_put(t_mlx_img	*img_data, int x, int y, int color)
{
	char	*dst;

	dst = img_data->addr + (y * img_data->line_length + x
			* (img_data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
