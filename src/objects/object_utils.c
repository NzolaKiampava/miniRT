/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:34:23 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:34:57 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Frees memory allocated for an object
 * @param obj Pointer to the object to free
 */
void	object_free(t_object *obj)
{
	if (!obj)
		return ;
	if (obj->data)
		free(obj->data);
	free(obj);
}
