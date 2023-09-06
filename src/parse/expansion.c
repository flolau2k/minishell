/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:01:55 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/06 11:46:28 by pcazac           ###   ########.fr       */
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

char	*expand(char *arg, char *new, t_shell *sh)
{
	int		i;

	i = 0;
	if (arg[i] && arg[i] == '$' && arg[i + 1] == '?')
	{
		i = is_special_variable(sh, &new);
		expand(arg + i, new, sh);
	}
	if (arg[i] && arg[i] == '$' && ft_isalpha(arg[i + 1]))
	{
		i = is_variable(sh, arg, &new);
		expand(arg + i, new, sh);
	}
	else if (arg[i] && arg[i] != '$' && arg[i + 1] != '?')
	{
		i = not_variable(arg, &new);
		expand(arg + i, new, sh);
	}
	return (new);
}

/// @brief ft_strdup the arguments and search for the environment expansions
/// @param arg Node of the exec command
void	expand_exec(t_exec *arg, t_shell *sh)
{
	char	*new;
	int		i;

	i = -1;
	new = NULL;
	while (arg->argv[++i])
		arg->argv[i] = expand(arg->argv[i], new, sh);
	arg->cmd = arg->argv[0];
}

/// @brief ft_strdup the arguments and search for the environment expansions
/// @param arg Node of the redirect command
void	expand_redir(t_redir *arg, t_shell *sh)
{
	char	*new;

	new = NULL;
	new = expand(arg->file, new, sh);
	arg->file = new;
	arg->efile = end_arg(new);
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
	if (cmd->type == NODE_EXEC)
		expand_exec((t_exec *)cmd, sh);
	else if (cmd->type == NODE_PIPE)
		travel_pipe((t_pipe *)cmd, sh);
	else if (cmd->type == NODE_REDIRECT)
		expand_redir((t_redir *)cmd, sh);
}
