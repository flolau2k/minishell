/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:27:08 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/08 20:29:59 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	precheck(char *arg)
{
	// bool	closed;
	int		i;

	i = 0;
	// closed = true;
	while (arg[i])
	{
		if (arg[i] == '\\')
			i++;
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] && arg[i] != '\'')
				i++;
			if (arg[i] != '\'')
				return (ft_printf("Quotes not closed\n"), false);
		}
		if (arg[i] == '"')
		{
			i++;
			while (arg[i] && arg[i] != '"')
				i++;
			if (arg[i] != '"')
				return (ft_printf("Quotes not closed\n"), false);
		}
		i++;
	}
	return (true);
}

/// @brief ft_strdup the arguments and search for the environment expansions
/// @param arg Node of the exec command
bool	quote_check_exec(t_exec *arg)
{
	int	i;

	i = -1;
	while (arg->argv[++i])
	{
		if (!precheck(arg->argv[i]))
			return (false);
	}
	return (true);
}

/// @brief ft_strdup the arguments and search for the environment expansions
/// @param arg Node of the redirect command
bool	quote_check_redir(t_redir *arg)
{
	if (!precheck(arg->file))
		return (false);
	if (arg->cmd)
		quote_check(arg->cmd);
	return (true);
}

bool	quote_check_pipe(t_pipe *arg)
{
	if (arg->left)
	{
		if (!quote_check(arg->left))
			return (false);
	}
	if (arg->right)
	{
		if (!quote_check(arg->right))
			return (false);
	}
	return (true);
}

/// @brief Travels through the tree and duplicates the arguments and expands
/// @param cmd Root node of the AST
bool	quote_check(t_cmd *cmd)
{
	if (cmd->type == NODE_EXEC)
	{
		if (!quote_check_exec((t_exec *)cmd))
			return (false);
	}
	else if (cmd->type == NODE_PIPE)
	{
		if (!quote_check_pipe((t_pipe *)cmd))
			return (false);
	}
	else if (cmd->type == NODE_REDIRECT)
	{
		if (!quote_check_redir((t_redir *)cmd))
			return (false);
	}
	return (true);
}
