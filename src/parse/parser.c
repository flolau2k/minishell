/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:01:17 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/28 11:28:46 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
				sh->ret = GENERAL_ERROR;
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
