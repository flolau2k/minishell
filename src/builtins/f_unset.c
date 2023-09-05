/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:35 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 16:00:42 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_unset(t_exec *cmd)
{
	if (cmd->argv[1])
		cmd->sh->env = unset_env(cmd->sh->env, cmd->argv[1]);
	return (EXIT_SUCCESS);
}
