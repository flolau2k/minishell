/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:01:17 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/26 17:57:32 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_copy_expand(t_list *token_str, t_shell *sh)
{
	while (token_str)
	{
		if (((t_token *)token_str->content)->type == DLESS && token_str->next)
			((t_token *)token_str->next->content)->type = SQUOTE;
		copy_expand(token_str->content, sh);
		token_str = token_str->next;
	}
}

bool	parser(t_list *token_str, t_cmd **root, t_shell *sh)
{
	t_list	*tmp;

	token_copy_expand(token_str, sh);
	token_str = unite_tokens(token_str);
	tmp = token_str;
	while (tmp)
	{
		if (token_str && !get_redirect(&token_str, root, sh))
			return(false);
		if (token_str && !get_word(&token_str, root, sh))
			return(false);
		if (token_str && !get_pipe(&token_str, root))
			return(false);
		tmp = token_str;
	}
	return (true);
}

bool	get_pipe(t_list **token_str, t_cmd **root)
{
	t_list	*tmp;
	t_token	*content;

	tmp = *token_str;
	content = (t_token *) tmp->content;
	if (content->type == PIPE)
	{	
		if (!tmp->next)
		{
			ft_error2(NULL, "unexpected token after Pipe!");
			return (false);
		}
		pipe_token(root);
		*token_str = tmp->next;
		free_token(tmp);
	}
	return (true);
}

bool	get_word(t_list **token_str, t_cmd **root, t_shell *sh)
{
	t_list	*tmp;
	t_list	*next;
	t_token	*content;
	char	**argv;

	tmp = *token_str;
	next = NULL;
	argv = NULL;
	content = (t_token *) tmp->content;
	while (tmp)
	{
		content = (t_token *) tmp->content;
		if (content->type == PIPE)
			break ;
		else
		{
			argv = array_addback(argv, content->start);
			if (tmp == *token_str)
				*token_str = tmp->next;
			next = tmp->next;
			free_token(tmp);
			tmp = next;
		}
	}
	if (!command_token(argv, root, sh))
		return (true);
	return (true);
}

bool	is_redir(t_list *lst)
{
	t_token *content;

	content = (t_token *) lst->content;
	if (content->type == LESS || content->type == DLESS
		|| content->type == GREATER || content->type == DGREATER)
		return (true);
	return (false);
}

bool	is_pipe(t_list *lst)
{
	t_token *content;

	content = (t_token *) lst->content;
	if (content->type == PIPE)
		return (true);
	return (false);
}

t_list	*delete_node(t_list **root, t_list *to_delete)
{
	t_list	*tmp;
	t_list	*next;

	if (*root == to_delete)
	{
		next = (*root)->next;
		free_token(*root);
		*root = next;
		return (next);
	}
	tmp = *root;
	while (tmp)
	{
		if (tmp->next && tmp->next == to_delete)
		{
			next = tmp->next->next;
			free_token(tmp->next);
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
		if (*token_str == tmp && is_redir(tmp))
		{
			if (tmp->next)
				delete_node(token_str, tmp->next);
			tmp = delete_node(token_str, tmp);
			(*token_str) = tmp;
		}
		else if (tmp->next && is_redir(tmp->next))
		{
			if (tmp->next->next)
				delete_node(token_str, tmp->next->next);
			tmp = delete_node(token_str, tmp->next);
		}
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
}

bool	get_redirect(t_list **token_str, t_cmd **root, t_shell *sh)
{
	t_list	*tmp;

	tmp = *token_str;
	while (tmp)
	{
		if (is_redir(tmp))
		{
			if (!redirect_token(&tmp, root, sh))
			{
				ft_error2(NULL, "unexpected token after redirect!");
				return (false); // unexpected token error
			}
		}
		else if (is_pipe(tmp))
			break ;
		else
			tmp = tmp->next;
	}
	clear_redirects(token_str);
	return (true);
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

void	reset_flags(t_list *tmp)
{
	t_token	*cont;
	t_token	*next;

	cont = (t_token *)tmp->content;
	next = (t_token *)tmp->next->content;
	cont->flag &= next->flag;
}

/// @brief delete empty nodes
/// @param root 
/// @param tmp 
t_list	*delete_empty_nodes(t_list *root)
{
	t_list	*tmp;
	t_list	*next;

	tmp = root;
	if (tmp && empty_node(tmp) && flag_node(tmp))
		tmp = delete_node(&root, tmp);
	while (tmp)
	{
		next = tmp->next;
		if (next && empty_node(next) && flag_node(tmp))
		{
			reset_flags(tmp);
			tmp = delete_node(&root, next);
		}
		else
			tmp = tmp->next;
	}
	return (root);
}

t_list	*unite_tokens(t_list *token_str)
{
	t_list	*tmp;

	// token_str = delete_empty_nodes(token_str);
	tmp = token_str;
	while (tmp)
	{
		if (tmp->next && unite(tmp))
			continue ;
		else
			tmp = tmp->next;
	}
	return (token_str);
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
		free_token(next);
		return (true);
	}
	return (false);
}

void	copy_expand(void *arg, t_shell *sh)
{
	t_token	*token;
	char	*temp;

	temp = NULL;
	token = (t_token *) arg;
	temp = ft_substr(token->start, 0, token->length);
	if (token->type == WORD || token->type == DQUOTE)
		temp = expand(temp, sh);
	if (token->type == DQUOTE || token->type == SQUOTE)
		token->type = WORD;
	token->start = temp;
}
