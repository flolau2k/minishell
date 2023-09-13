/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:27:08 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/13 15:38:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Checks that there are no open quotes
/// @param arg Initial argument string
/// @return true if quotes are closed, false if not
bool	quote_check(char *arg)
{
	int		i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] && arg[i] == '\'')
		{
			i++;
			while (arg[i] && arg[i] != '\'')
				i++;
			if (arg[i] != '\'')
				return (ft_printf("Quotes not closed\n"), false);
		}
		if (arg[i] && arg[i] == '\"')
		{
			i++;
			while (arg[++i] && arg[i] != '\"')
				i++;
			if (arg[i] != '"')
				return (ft_printf("Quotes not closed\n"), false);
		}
	}
	return (true);
}
