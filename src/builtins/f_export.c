/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:33 by flauer            #+#    #+#             */
/*   Updated: 2023/09/28 09:30:27 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_export(t_exec *cmd)
{
	char	*key;
	char	*new;

	new = cmd->argv[1];
	if (!new)
		return (f_env(cmd));
	if (ft_strchr(new, '='))
	{
		key = ft_substr(new, 0, ft_strchr(new, '=') - new);
		if (!is_valid_identfier(key))
		{
			ft_error2(new, "not a valid identifier");
			free_exec(cmd);
			return (GENERAL_ERROR);
		}
		if (get_env(cmd->sh->env, key))
		{
			if (!replace_in_env(cmd->sh->env, new))
				ft_error(NULL, "failure in replacing env!", BUILTIN_MISUSE);
		}
		else
			cmd->sh->env = set_env(cmd->sh->env, new);
		free(key);
	}
	free_exec(cmd);
	return (EXIT_SUCCESS);
}
