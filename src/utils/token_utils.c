/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:46:19 by pcazac            #+#    #+#             */
/*   Updated: 2023/08/31 11:25:48 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/// @brief Allocates new array copies and frees old arary
/// @param array Old array to be expanded
/// @param count Number of cells to be added
/// @return Total number of cells
int	new_arr(t_array *array, int count)
{
	t_array	new;
	int		i;

	i = 0;
	count += array_length(array->start);
	new.start = ft_calloc(count + 1, sizeof(char *));
	if (!(new.start))
			ft_error("Allocation erorr", GENERAL_ERROR);
	new.end = ft_calloc(count + 1, sizeof(char *));
	if (!(new.end))
			ft_error("Allocation erorr", GENERAL_ERROR);
	while (array->start[i])
	{
		new.start[i] = array->start[i];
		new.end[i] = array->end[i];
		i++;
	}
	free(array->start);
	free(array->end);
	array->start = new.start;
	array->end = new.end;
	return (count);
}
