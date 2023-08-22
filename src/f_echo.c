/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:26 by flauer            #+#    #+#             */
/*   Updated: 2023/08/22 14:14:51 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	f_echon(t_exec *cmd)
{
	int	i;

	i = 2;
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		i++;
	}
	return ;
}

void	f_echo(t_exec *cmd)
{
	int	i;

	i = 1;
	if (cmd->argv[1] && ft_strncmp(cmd->argv[1], "-n", 3) == 0)
		return (f_echon(cmd));
	while (cmd->argv[i])
	{
		printf("%s\n", cmd->argv[i]);
		i++;
	}
	return ;
}
