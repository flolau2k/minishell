/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:01:17 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/10 16:46:24 by flauer           ###   ########.fr       */
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
		if (tmp && !get_redirect(&tmp, root, sh))
			return (false);
		if (tmp && !get_word(&tmp, root, sh))
			return (false);
		if (tmp && !get_pipe(&tmp, root, sh))
			return (false);
	}
	return (true);
}

bool	get_pipe(t_list **token_str, t_cmd **root, t_shell *sh)
{
	t_list	*tmp;
	t_token	*content;

	tmp = *token_str;
	content = (t_token *) tmp->content;
	if (content->type == PIPE)
	{
		if (!*root)
		{
			sh->ret = BUILTIN_MISUSE;
			return (ft_error2(NULL, "unexpected token before Pipe!",
					NULL, false));
		}
		if (!tmp->next)
		{
			sh->ret = BUILTIN_MISUSE;
			return (ft_error2(NULL, "unexpected token after Pipe!",
					NULL, false));
		}
		pipe_token(root, sh);
		*token_str = tmp->next;
	}
	return (true);
}

bool	get_word(t_list **token_str, t_cmd **root, t_shell *sh)
{
	t_list	*tmp;
	t_token	*content;
	char	**argv;

	tmp = *token_str;
	argv = NULL;
	content = (t_token *) tmp->content;
	while (tmp)
	{
		content = (t_token *) tmp->content;
		if (content->type == PIPE)
			break ;
		else if (is_redir(tmp))
			tmp = tmp->next->next;
		else
		{
			argv = array_addback(argv, content->start);
			tmp = tmp->next;
		}
	}
	*token_str = tmp;
	command_token(argv, root, sh);
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
				sh->ret = BUILTIN_MISUSE;
				return (ft_error2(NULL, "unexpected token after redirect!",
						NULL, false));
			}
		}
		else if (is_pipe(tmp))
			break ;
		else
			tmp = tmp->next;
	}
	return (true);
}
