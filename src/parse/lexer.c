/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:27:21 by flauer            #+#    #+#             */
/*   Updated: 2023/09/26 15:05:53 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*do_lexing(char *arg)
{
	int		i;
	t_list	*ret;

	i = 0;
	ret = NULL;
	while (arg[i])
	{
		while (arg[i] && ft_isspace(arg[i]))
			i++;
		if (arg[i] && arg[i] == '<' && arg[i + 1] && arg[i + 1] == '<')
			i += l_dless(&ret, arg + i);
		else if (arg[i] && arg[i] == '>' && arg[i + 1] && arg[i + 1] == '>')
			i += l_dgreater(&ret, arg + i);
		else if (arg[i] && arg[i] == '>')
			i += l_greater(&ret, arg + i);
		else if (arg[i] && arg[i] == '<')
			i += l_less(&ret, arg + i);
		else if (arg[i] && arg[i] == '\"')
			i += l_dquote(&ret, arg + i);
		else if (arg[i] && arg[i] == '\'')
			i += l_squote(&ret, arg + i);
		else if (arg[i] && arg[i] == '|')
			i += l_pipe(&ret, arg + i);
		else if (arg[i])
			i += l_word(&ret, arg + i);
	}
	return (ret);
}
