/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:35 by flauer            #+#    #+#             */
/*   Updated: 2023/09/13 15:37:14 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_unset(t_exec *cmd)
{
	if (cmd->argv[1])
		cmd->sh->env = unset_env(cmd->sh->env, cmd->argv[1]);
	free_exec(cmd);
	return (EXIT_SUCCESS);
}
