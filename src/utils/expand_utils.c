/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:04:59 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/28 10:07:48 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_variable(t_shell *sh, char *arg, char **new)
{
	int		i;
	char	*key;
	char	*temp;

	key = NULL;
	temp = NULL;
	i = 0;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
				i++;
	key = ft_substr(arg, 0, i);
	if (!key)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	temp = get_env(sh->env, key);
	if (!temp)
	{	
		free(key);
		*new = ft_strdup("");
		return (i);
	}
	*new = ft_strdup(temp);
	free(key);
	return (i);
}

int	not_variable(char *arg, char **val)
{
	int		i;

	i = 0;
	while (arg[i] && (arg[i] != '$' || (arg[i] == '$' && (ft_isspace(arg[i + 1]) || !arg[i + 1]))))
		i++;
	*val = ft_substr(arg, 0, i);
	if (i > 0)
		i--;
	if (!*val)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	return (i);
}

void	copy_expand(void *arg, t_shell *sh)
{
	t_token	*token;
	char	*temp;
	char	*expanded_temp;

	temp = NULL;
	expanded_temp = NULL;
	token = (t_token *) arg;
	temp = ft_substr(token->start, 0, token->length);
	if (token->type == WORD || token->type == DQUOTE)
	{
		expanded_temp = expand(temp, sh);
		free(temp);
		temp = expanded_temp;
	}
	if (token->type == DQUOTE || token->type == SQUOTE)
		token->type = WORD;
	token->start = temp;
}

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
