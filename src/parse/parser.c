/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:01:17 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/22 17:14:14 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_copy_expand(t_list *token_str, t_shell *sh)
{
	while (token_str)
	{
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
		return (false);
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

void	clear_redirects(t_list **token_str)
{
	t_list	*tmp;
	t_list	*smt;
	
	tmp = *token_str;
	while (tmp)
	{
		if (*token_str == tmp && is_redir(tmp))
		{
			(*token_str) = tmp->next->next;
			free_token(tmp->next);
			free_token(tmp);
		}
		else if (tmp->next && is_redir(tmp->next))
		{
			smt = tmp->next->next->next;
			free_token(tmp->next->next);
			free_token(tmp->next);
			tmp->next = smt;
		}
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
				return (false); // unexpected token error
		}
		else if (is_pipe(tmp))
			break ;
		else
			tmp = tmp->next;
	}
	clear_redirects(token_str);
	return (true);
}

t_list	*unite_tokens(t_list *token_str)
{
	t_list	*tmp;

	tmp = token_str;
	while(tmp)
	{
		if (tmp->next)
			check_and_unite(tmp);
		tmp = tmp->next;
	}
	return (token_str);
}

void	check_and_unite(t_list *tmp)
{
	t_list	*next;
	t_token	*val[2];
	char	*temp;

	next = tmp->next;
	val[0] = (t_token *) tmp->content;
	val[1] = (t_token *) next->content;
	if (val[0]->flag)
	{
		temp = val[0]->start;
		val[0]->start = ft_strjoin(temp, val[1]->start);
		val[0]->type = WORD;
		free(temp);
		tmp->next = next->next;
		free_token(next);
	}
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
	token->start = temp;
}
