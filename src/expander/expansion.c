/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:01:55 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/05 22:15:12 by pcazac           ###   ########.fr       */
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

bool	expand(char *arg, char **new, t_shell *sh)
{
	int		i;
	int		count;
	char	*key;
	char	*smth;

	smth = NULL;
	key = NULL;
	count = 0;
	i = 0;
	while (arg[i])
	{
		// if (arg[i] && arg[i] == '$' && arg[i + 1] == '?')
		// {
			
		// }
		if (arg[i] && arg[i] == '$' && ft_isalpha(arg[i + 1]))
		{
			while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
				count++;
			key = ft_calloc (count + 1, sizeof(char));
			if (!key)
				ft_error("ALLOCATION ERROR", GENERAL_ERROR);
			ft_strcpy(key, arg[i], count);
			smth = get_env(sh->env, key);
			free(key);
			if (!*new)
				*new = smth;
			else if (*new)
				ft_strjoin(new, smth);
			if (*new)
				free(*new);
			
		}
		expand_var();
		i++;
	}
	if (arg[i])
		is_var(arg + i, new);
}

/// @brief ft_strdup the arguments and search for the environment expansions
/// @param arg Node of the exec command
void	expand_exec(t_exec *arg, t_shell *sh)
{
	
}

/// @brief ft_strdup the arguments and search for the environment expansions
/// @param arg Node of the redirect command
void	expand_redir(t_redir *arg, t_shell *sh)
{
	char	*new;

	expand(arg->file, &new, sh);
	arg->file = new;
	arg->efile = end_arg(new);
	if (arg->cmd)
		expander(arg->cmd, sh);
}

void	travel_pipe(t_pipe *arg, t_shell *sh)
{
	if (arg->left)
		expander(arg->left, sh);
	if (arg->right)
		expander(arg->right, sh);
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
