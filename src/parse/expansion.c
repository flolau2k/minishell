/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:01:55 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/06 10:24:34 by pcazac           ###   ########.fr       */
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
	int		count;
	char	*key;
	char	*smth;
	char	*smth2;

	smth = NULL;
	smth2 = NULL;
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
			while (arg[++i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
				count++;
			key = ft_substr(arg + i - count, 0, count);
			if (!key)
				ft_error("ALLOCATION ERROR", GENERAL_ERROR);
			smth = get_env(sh->env, key);
			free(key);
			if (!new)
			{
				new = smth;
				expand(arg + i, new, sh);
			}
			else if (new)
				smth2 = ft_strjoin(new, smth);
			// free(smth);
			// free(new);
			new = smth2;
			expand(arg + i, new, sh);
		}
		else
		{
			count = 0;
			while (arg[i])
			{
				if (arg[i] && arg[i] == '$')
					break;
				count++;
				i++;
			}
			smth = ft_substr(arg + i - count, 0, count);
			if (!smth)
				ft_error("ALLOCATION ERROR", GENERAL_ERROR);
			if (!new)
			{
				new = smth;
				expand(arg + i, new, sh);
			}
			else
			{
				smth2 = ft_strjoin(new, smth);
				// free(new);
				// free(smth);
				new = smth2;
			}
				expand(arg + i, new, sh);
		}
		// i++;
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
