/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:54:59 by flauer            #+#    #+#             */
/*   Updated: 2023/09/29 16:23:30 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_env(t_exec *cmd)
{
	int	i;

	i = 0;
	if (num_args(cmd->argv) > 1)
	{
		free_exec(cmd);
		return (ft_error2("env", "does not take arguments!",
				NULL, GENERAL_ERROR));
	}
	while (cmd->sh->env[i])
	{
		if (ft_strlen(cmd->sh->env[i]) > 0)
			printf("%s\n", cmd->sh->env[i]);
		i++;
	}
	free_exec(cmd);
	return (EXIT_SUCCESS);
}
