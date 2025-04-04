/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:22:09 by nkiampav          #+#    #+#             */
/*   Updated: 2025/04/04 11:22:57 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Count the number of elements in a NULL-terminated array
*/
int	count_elements(char **elements)
{
	int	count;

	count = 0;
	while (elements[count])
		count++;
	return (count);
}

/**
 * Free a NULL-terminated array of strings
*/
void	free_split(char **split)
{
	int	i;
	
	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}