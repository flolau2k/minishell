/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:33 by flauer            #+#    #+#             */
/*   Updated: 2023/09/29 10:04:05 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**put_in_env(char **env, char *new, char *key)
{
	if (get_env(env, key))
		replace_in_env(env, new);
	else
		env = set_env(env, new);
	free(key);
	return (env);
}

int	f_export(t_exec *cmd)
{
	char	*key;
	char	*new;
	int		i;

	i = 1;
	while (cmd->argv[i])
	{
		new = cmd->argv[i];
		if (ft_strchr(new, '='))
		{
			key = ft_substr(new, 0, ft_strchr(new, '=') - new);
			if (!is_valid_identfier(key))
			{
				ft_error2(key, "not a valid identifier", key);
				i++;
				continue ;
			}
			cmd->sh->env = put_in_env(cmd->sh->env, new, key);
		}
		i++;
	}
	if (i == 1)
		return (f_env(cmd));
	free_exec(cmd);
	return (EXIT_SUCCESS);
}
