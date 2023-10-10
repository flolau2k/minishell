/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:27:21 by flauer            #+#    #+#             */
/*   Updated: 2023/10/10 12:41:15 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	if_redir(char *arg, int i)
{
	if (arg[i] && arg[i] == '<' && arg[i + 1] && arg[i + 1] == '<')
		return (true);
	else if (arg[i] && arg[i] == '>' && arg[i + 1] && arg[i + 1] == '>')
		return (true);
	else if (arg[i] && arg[i] == '>')
		return (true);
	else if (arg[i] && arg[i] == '<')
		return (true);
	return (false);
}

int	get_redir(t_list **ret, char *arg, int i)
{
	int	j;

	j = 0;
	if (arg[i] && arg[i] == '<' && arg[i + 1] && arg[i + 1] == '<')
		j = l_dless(ret, arg + i);
	else if (arg[i] && arg[i] == '>' && arg[i + 1] && arg[i + 1] == '>')
		j = l_dgreater(ret, arg + i);
	else if (arg[i] && arg[i] == '>')
		j = l_greater(ret, arg + i);
	else if (arg[i] && arg[i] == '<')
		j = l_less(ret, arg + i);
	return (j);
}

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
		if (if_redir(arg, i))
			i += get_redir(&ret, arg, i);
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
