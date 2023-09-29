/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:35 by flauer            #+#    #+#             */
/*   Updated: 2023/09/29 16:23:23 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_unset(t_exec *cmd)
{
	int	i;

	i = 0;
	cmd->sh->ret = 0;
	while (cmd->argv[i])
	{
		if (!is_valid_identfier(cmd->argv[i], false))
			ft_error4(cmd->sh, cmd->argv[i], "not a valid identifier", NULL);
		else
			cmd->sh->env = unset_env(cmd->sh->env, cmd->argv[i]);
		i++;
	}
	free_exec(cmd);
	return (cmd->sh->ret);
}
