/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:23:26 by flauer            #+#    #+#             */
/*   Updated: 2023/09/15 11:24:56 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief free a string array and it's contents.
/// @param arr array
void	free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/// @brief get lenth of string array
/// @param arr array
/// @return length
int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void	wait_exit(void)
{
	pid_t	pid;

	pid = waitpid(0, NULL, 0);
	while (pid != -1)
		pid = waitpid(0, NULL, 0);
}
