/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:01:55 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/08 14:43:36 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Returns the pointer to the end of the string
/// @param s Input string
/// @return A pointer to the end of the string
char	*end_arg(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (s+i);
}

/// @brief Expands each string passed
/// @param arg String from the token
/// @param sh Shell struct pointer
/// @return The string of expanded command
char	*expand(char *arg, t_shell *sh)
{
	int		i;
	char	*ret;
	// bool	closed;

	i = 0;
	ret = NULL;
	// if (arg[i] && arg[i] == '\'')
	// 	ret = ft_substr(arg);
	while (arg[i])
	{
		if (arg[i] && arg[i + 1] && arg[i] == '$' && arg[i + 1] == '?')
			i += get_special_var(sh, &ret);
		else if (arg[i] && arg[i + 1] && arg[i] == '$' && ft_isalpha(arg[i + 1]))
			i += get_variable(sh, arg + i, &ret);
		else if (arg[i] && arg[i + 1] && arg[i] != '$' && arg[i + 1] != '?')
			i += get_non_variable(arg + i, &ret);
	}
	return (ret);
}

/// @brief ft_strdup the arguments and search for the environment expansions
/// @param arg Node of the exec command
void	expand_exec(t_exec *arg, t_shell *sh)
{
	int	i;

	i = -1;
	while (arg->argv[++i])
		arg->argv[i] = expand(arg->argv[i], sh);
	arg->cmd = arg->argv[0];
}

/// @brief ft_strdup the arguments and search for the environment expansions
/// @param arg Node of the redirect command
void	expand_redir(t_redir *arg, t_shell *sh)
{
	arg->file = expand(arg->file, sh);
	arg->efile = end_arg(arg->file);
	if (arg->cmd)
		expander(sh, arg->cmd);
}

void	travel_pipe(t_pipe *arg, t_shell *sh)
{
	if (arg->left)
		expander(sh, arg->left);
	if (arg->right)
		expander(sh, arg->right);
}

/// @brief Travels through the tree and duplicates the arguments and expands
/// @param cmd Root node of the AST
void	expander(t_shell *sh, t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == NODE_EXEC)
		expand_exec((t_exec *)cmd, sh);
	else if (cmd->type == NODE_PIPE)
		travel_pipe((t_pipe *)cmd, sh);
	else if (cmd->type == NODE_REDIRECT)
		expand_redir((t_redir *)cmd, sh);
}