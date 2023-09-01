/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:26 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 16:49:07 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_echo(t_exec *cmd)
{
	int		i;
	bool	nl;

	nl = true;
	i = 1;
	if (cmd->argv[1] && ft_strncmp(cmd->argv[1], "-n", 3) == 0)
	{
		nl = false;
		i = 2;
	}
	while (cmd->argv[i] && cmd->argv[i + 1])
	{
		printf("%s ", cmd->argv[i]);
		i++;
	}
	printf("%s", cmd->argv[i]);
	if (nl)
		printf("\n");
	return (EXIT_SUCCESS);
}
