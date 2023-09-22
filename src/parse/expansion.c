/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:01:55 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/22 18:08:24 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Returns the pointer to the end of the string
/// @param s Input string
/// @return A pointer to the end of the string
char	*end_arg(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (s+i);
}

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
	while (arg[i])
	{
		if (arg[i] && arg[i + 1] && arg[i] == '$' && arg[i + 1] == '?')
			i += get_special_var(sh, &ret);
		else if (arg[i] && arg[i + 1] && arg[i] == '$' && ft_isalpha(arg[i + 1]))
			i += get_variable(sh, arg + i, &ret);
		else
			i += get_non_variable(arg + i, &ret);
		i++;
	}
	return (ret);
}
