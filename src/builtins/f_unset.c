/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:35 by flauer            #+#    #+#             */
/*   Updated: 2023/09/29 12:46:54 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_unset(t_exec *cmd)
{
	cmd->sh->ret = 0;
	if (cmd->argv[1])
	{
		if (!is_valid_identfier(cmd->argv[1], false))
			ft_error4(cmd->sh, cmd->argv[1], "not a valid identifier", NULL);
		else
			cmd->sh->env = unset_env(cmd->sh->env, cmd->argv[1]);
	}
	free_exec(cmd);
	return (cmd->sh->ret);
}
