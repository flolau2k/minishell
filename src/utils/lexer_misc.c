/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:48:06 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/12 12:00:06 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(void *arg)
{
	t_token	*cont;

	cont = (t_token *) arg;
	free(cont->start);
	free(cont);
}

int	l_pipe(t_list **ret, char *arg)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = PIPE;
	token->length = 1;
	token->start = arg;
	token->heredoc = false;
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
	token = ft_calloc(1, sizeof(t_token));
	if (arg[i + 1] && !ft_isspace(arg[i +1]))
		token->flag = true;
	token->type = DQUOTE;
	token->start = arg + 1;
	token->length = i - 1;
	token->heredoc = false;
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
	token = ft_calloc(1, sizeof(t_token));
	token->type = SQUOTE;
	token->start = arg + 1;
	if (arg[i + 1] && !ft_isspace(arg[i +1]))
		token->flag = true;
	token->heredoc = false;
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
	token->heredoc = true;
	ft_lstadd_back(ret, ft_lstnew(token));
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	return (i);
}
