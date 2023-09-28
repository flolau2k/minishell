/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:18:48 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/28 17:23:23 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*delete_node(t_list **root, t_list *to_delete)
{
	t_list	*tmp;
	t_list	*next;

	if (*root == to_delete)
	{
		next = (*root)->next;
		ft_lstdelone(*root, &free_token);
		*root = next;
		return (next);
	}
	tmp = *root;
	while (tmp)
	{
		if (tmp->next && tmp->next == to_delete)
		{
			next = tmp->next->next;
			ft_lstdelone(tmp->next, &free_token);
			tmp->next = next;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	clear_redirects(t_list **token_str)
{
	t_list	*tmp;
	t_token	*content;
	
	tmp = *token_str;
	while (tmp)
	{
		content = (t_token *) tmp->content;
		if (content->type == PIPE)
			break ;
		if (tmp && is_redir(tmp))
		{
			if (tmp->next)
				delete_node(token_str, tmp->next);
			tmp = delete_node(token_str, tmp);
		}
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
}

bool	unite(t_list *tmp)
{
	t_list	*next;
	t_token	*val[2];
	char	*temp;

	next = tmp->next;
	val[0] = (t_token *) tmp->content;
	val[1] = (t_token *) next->content;
	if (val[0]->flag && (val[1]->type == WORD || val[1]->type == DQUOTE || val[1]->type == SQUOTE))
	{
		temp = val[0]->start;
		val[0]->start = ft_strjoin_s(temp, val[1]->start);
		val[0]->type = WORD;
		val[0]->flag = val[1]->flag;
		free(temp);
		tmp->next = next->next;
		ft_lstdelone(next, &free_token);
		return (true);
	}
	return (false);
}