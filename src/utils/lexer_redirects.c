/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:38:16 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/18 14:49:47 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	l_dless(t_list **ret, char *arg)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = DLESS;
	token->length = 2;
	token->start = arg;
	ft_lstadd_back(ret, ft_lstnew(token));
	return (token->length);
}

int	l_dgreater(t_list **ret, char *arg)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = DGREATER;
	token->length = 2;
	token->start = arg;
	ft_lstadd_back(ret, ft_lstnew(token));
	return (token->length);
}

int	l_greater(t_list **ret, char *arg)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = GREATER;
	token->length = 1;
	token->start = arg;
	ft_lstadd_back(ret, ft_lstnew(token));
	return (token->length);
}

int	l_less(t_list **ret, char *arg)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = LESS;
	token->length = 1;
	token->start = arg;
	ft_lstadd_back(ret, ft_lstnew(token));
	return (token->length);
}
