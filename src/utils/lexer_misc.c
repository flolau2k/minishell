/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:48:06 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/25 11:10:39 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(t_list *elm)
{
	t_token	*cont;

	cont = (t_token *) elm->content;
	free(cont->start);
	free(cont);
	free(elm);
}

int	l_pipe(t_list **ret, char *arg)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = PIPE;
	token->length = 1;
	token->start = arg;
	ft_lstadd_back(ret, ft_lstnew(token));
	return (token->length);
}

int	l_dquote(t_list **ret, char *arg)
{
	t_token	*token;
	int		i;

	i = 1;
	while (arg[i] && arg[i] != '\"')
		i++;
	if (i == 1)
		return (++i);
	token = ft_calloc(1, sizeof(t_token));
	if (arg[i + 1] && !ft_isspace(arg[i +1]))
		token->flag = true;
	token->type = DQUOTE;
	token->start = arg + 1;
	token->length = i - 1;
	ft_lstadd_back(ret, ft_lstnew(token));
	return (++i);
}
int	l_squote(t_list **ret, char *arg)
{
	t_token	*token;
	int		i;

	i = 1;
	while (arg[i] && arg[i] != '\'')
		i++;
	if (i == 1)
		return (++i);
	token = ft_calloc(1, sizeof(t_token));
	token->type = SQUOTE;
	token->start = arg + 1;
	if (arg[i + 1] && !ft_isspace(arg[i +1]))
		token->flag = true;
	token->length = i - 1;
	ft_lstadd_back(ret, ft_lstnew(token));
	return (++i);
}

int	l_word(t_list **ret, char *arg)
{
	t_token	*token;
	int		i;

	i = 0;
	token = ft_calloc(1, sizeof(t_token));
	token->type = WORD;
	while (arg[i] && !ft_strchr(A_CHAR, arg[i]) && !ft_isspace(arg[i]))
		i++;
	if (arg[i] && !ft_isspace(arg[i]) && ft_strchr("\"\'", arg[i]))
		token->flag = true;
	token->length = i;
	token->start = arg;
	ft_lstadd_back(ret, ft_lstnew(token));
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	return (i);
}
