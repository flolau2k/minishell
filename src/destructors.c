/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:13:10 by flauer            #+#    #+#             */
/*   Updated: 2023/08/22 15:22:22 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_carr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}

void	free_exec(t_exec **arg)
{
	free((*arg)->cmd);
	free_carr((*arg)->argv);
	free((*arg)->eargv);
	free((*arg));
	*arg = NULL;
}

// void	free_pipe(t_pipe **arg)
// {
// 	free((*arg));
// 	*arg = NULL;
// }

// void	free_redir(t_redir **arg)
// {
// 	free((*arg)->file);
// 	free((*arg));
// }
