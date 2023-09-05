/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:33 by flauer            #+#    #+#             */
/*   Updated: 2023/09/05 11:49:58 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_export(t_exec *cmd)
{
	char	*var;
	char	*newvar;
	char	*newval;

	if (!cmd->argv[1])
		f_env(cmd);
	newvar = cmd->argv[1];
	newval = ft_strchr(newvar, '=');
	if (newval)
	{
		*newval = '\0';
		newval++;
	}
	var = get_env(cmd->sh->env, newvar);
	if (ft_strchr(cmd->argv[1], '='))
		cmd->sh->env = set_env(cmd->sh->env, cmd->argv[1]);
	return (EXIT_SUCCESS);
}
