/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:54:59 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 15:52:21 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_env(t_exec *cmd)
{
	int	i;

	i = 0;
	while (cmd->sh->env[i])
	{
		if (ft_strlen(cmd->sh->env[i]) > 0)
			printf("%s\n", cmd->sh->env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
