/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:01:55 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/07 09:06:05 by pcazac           ###   ########.fr       */
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

char	*expand(char *arg, t_shell *sh)
{
	int		i;
	int		count;
	char	*new;
	char	*ret;
	char	*s;

	i = 0;
	count = 0;
	s = NULL;
	new = NULL;
	ret = NULL;
	while (arg[i])
	{
		if (arg[i] && arg[i] == '$' && arg[i + 1] == '?')
		{
			i += is_special_variable(sh, &s);
			if (s)
				count += ft_strlen(s);
			if (ret)
				new = ft_strdup(ret);
			else
				new = NULL;
			free(ret);
			ret = ft_realloc(new, s, count);
		}
		else if (arg[i] && arg[i] == '$' && ft_isalpha(arg[i + 1]))
		{
			i += is_variable(sh, arg + i, &s);
			if (s)
				count += ft_strlen(s);
			if (ret)
				new = ft_strdup(ret);
			else
				new = NULL;
			free(ret);
			ret = ft_realloc(new, s, count);
			// free(s);
		}
		else if (arg[i] && arg[i] != '$' && arg[i + 1] != '?')
		{
			i += not_variable(arg + i, &s);
			if (s)
				count += ft_strlen(s);
			if (ret)
				new = ft_strdup(ret);
			else
				new = NULL;
			// free(ret);
			ret = ft_realloc(new, s, count);
			free(s);
		}
	}
	return (ret);
}

/// @brief ft_strdup the arguments and search for the environment expansions
/// @param arg Node of the exec command
void	expand_exec(t_exec *arg, t_shell *sh)
{
	int		i;
	char	*new;

	i = -1;
	new = NULL;
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
	if (cmd->type == NODE_EXEC)
		expand_exec((t_exec *)cmd, sh);
	else if (cmd->type == NODE_PIPE)
		travel_pipe((t_pipe *)cmd, sh);
	else if (cmd->type == NODE_REDIRECT)
		expand_redir((t_redir *)cmd, sh);
}


// char	*expand(char *arg, char *new, t_shell *sh)
// {
// 	int		i;
// 	char	*s;
// 	char	*s2;
	
// 	s = NULL;
// 	s2 = NULL;
// 	i = 0;
// 	if (arg[i] && arg[i] == '$' && arg[i + 1] == '?')
// 	{
// 		i = is_special_variable(sh, &s);
// 		if (!new)
// 			new = s;
// 		else
// 		{
// 			s2 = ft_strjoin(new, s);
// 			free(s);
// 			free(new);
// 			new = s2;
// 		}
// 		expand(arg + i, new, sh);
// 	}
// 	else if (arg[i] && arg[i] == '$' && ft_isalpha(arg[i + 1]))
// 	{
// 		i = is_variable(sh, arg, &s);
// 		if (!new)
// 			new = s;
// 		else
// 		{
// 			s2 = ft_strjoin(new, s);
// 			free(s);
// 			free(new);
// 			new = s2;
// 		}
// 		expand(arg + i, new, sh);
// 	}
// 	else if (arg[i] && arg[i] != '$' && arg[i + 1] != '?')
// 	{
// 		i = not_variable(arg, &s);
// 		if (!new)
// 			new = s;
// 		else
// 		{
// 			s2 = ft_strjoin(new, s);
// 			free(s);
// 			printf("%p", new);
// 			printf("%s", new);
// 			free(new);
// 			new = s2;
// 		}
// 		expand(arg + i, new, sh);
// 	}
// 	return (new);
// }