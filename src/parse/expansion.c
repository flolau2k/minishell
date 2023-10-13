/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:01:55 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/13 08:36:01 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Expands each string passed
/// @param arg String from the token
/// @param sh Shell struct pointer
/// @return The string of expanded command
char	*expand(char *arg, t_shell *sh)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (!arg[i])
		return (ft_strdup(""));
	while (arg[i])
	{
		if (arg[i] && arg[i + 1] && arg[i] == '$' && arg[i + 1] == '?')
			i += get_special_var(sh, &ret);
		else if (arg[i] && arg[i + 1] && arg[i] == '$'
			&& ft_isalpha(arg[i + 1]))
			i += get_variable(sh, arg + i, &ret);
		else
			i += get_non_variable(arg + i, &ret);
		i++;
	}
	return (ret);
}
