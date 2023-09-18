/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:01:17 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/18 19:06:26 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	parser(t_list *token_str, t_cmd **root, t_shell *sh)
{
	t_list	*tmp;
	t_token	*content;

	ft_lstiter(token_str, &copy_expand);
	token_str = unite_tokens(token_str);
	tmp = token_str;
	while (tmp)
	{
		if (get_redirect(&token_str, root, sh))
			return(false);
		if (get_word(&token_str, root, sh))
			return(false);
		if (get_pipe(&token_str, root, sh))
			return(false);
		tmp = token_str;
	}
}

bool	get_word(t_list **token_str, t_cmd **root, t_shell *sh)
{
	t_list	*tmp;
	t_list	*next;
	t_token	*content;

	tmp = token_str;
	content = (t_token *) tmp->content;
	while (tmp)
	{
		content = (t_token *) tmp->content;
		if (content->type == PIPE)
			break ;
		else
		{
			if (!command_token(&tmp, root, sh))
				return (false);
			if (tmp == token_str)
				token_str = tmp->next->next;
			next = tmp->next;
			free_token(next);
			free(tmp);
			tmp = next->next;
			free_token(next);
			free(next);
		}
	}
}

bool	get_redirect(t_list **token_str, t_cmd **root, t_shell *sh)
{
	t_list	*tmp;
	t_list	*next;
	t_token	*content;

	tmp = token_str;
	content = (t_token *) tmp->content;
	while (tmp)
	{
		content = (t_token *) tmp->content;
		if (content->type == LESS || content->type == DLESS
			|| content->type == GREATER || content->type == DGREATER)
		{
			if (!redirect_token(&tmp, root, sh))
				return (false);
			if (tmp == token_str)
				token_str = tmp->next->next;
			next = tmp->next;
			free(tmp);
			tmp = next->next;
			free_token(next);
		}
		else if (content->type == PIPE)
			break ;
		else
			tmp = tmp->next;
	}
}

t_list	*unite_tokens(t_list **token_str)
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

// bool	parser(t_list	*token_str, t_cmd **root, t_shell *sh)
// {
// 	t_list	*tmp;
// 	t_token	*content;

// 	ft_lstiter(token_str, &copy_expand);
// 	token_str = unite_tokens(token_str);
// 	tmp = token_str;
// 	while (tmp)
// 	{
// 		content = (t_token *) tmp->content;
// 		if (content->type == LESS || content->type == DLESS
// 			|| content->type == GREATER || content->type == DGREATER)
// 		{
// 			if (!redirect_token(&tmp, root, sh))
// 				return (false);
// 		}
// 		else if (content->type == WORD || content->type == SQUOTE
// 				|| content->type == DQUOTE)
// 		{
// 			if (!command_token(&tmp, root, sh))
// 				return (false);
// 		}
// 		else if (content->type == PIPE)
// 		{
// 			if (!pipe_token(&tmp, root))
// 				return (false);
// 		}
// 		tmp = tmp->next;
// 	}
// }
