/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:19:55 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/29 16:24:54 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_redir(t_list *lst)
{
	t_token	*content;

	content = (t_token *) lst->content;
	if (content->type == LESS || content->type == DLESS
		|| content->type == GREATER || content->type == DGREATER)
		return (true);
	return (false);
}

bool	is_pipe(t_list *lst)
{
	t_token	*content;

	content = (t_token *) lst->content;
	if (content->type == PIPE)
		return (true);
	return (false);
}

bool	empty_node(t_list *node)
{
	t_token	*val;

	val = (t_token *) node->content;
	if (!val || !val->start || val->length == 0)
		return (true);
	return (false);
}

bool	flag_node(t_list *node)
{
	t_token	*val;

	val = (t_token *) node->content;
	if (val->flag)
		return (true);
	return (false);
}

bool	not_special_type(t_list *node)
{
	t_token	*val;

	val = (t_token *) node->content;
	if (val->type == SQUOTE || val->type == DQUOTE || val->type == WORD)
		return (true);
	else
		return (false);
}
