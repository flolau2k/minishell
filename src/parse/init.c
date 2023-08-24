/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:59 by flauer            #+#    #+#             */
/*   Updated: 2023/08/24 14:02:50 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


/// @brief Finds the root node for the AST
/// @param instr The initial argument string
/// @return A node that is the root
t_cmd *find_root(char *instr)
{
	char	*root;

	root = ft_calloc(1, sizeof(char *));
	root = ft_strchr(instr, '|');
	if (root)
		return (pipe_root(root));
	root = is_redirect(instr);
	if (root)
		return (redirect_root(root));
	else 
		return (cmd_root(instr));
}

static void	free_tokens(char ***tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

bool	init(t_shell *shell, int argc, char **argv, char **env)
{
	int	i;

	i = 1;
	*shell = (t_shell){};
	shell->tokens = ft_calloc(argc, sizeof(char *));
	if (!shell->tokens)
		return (false);
	while (i < argc)
	{
		shell->tokens[i - 1] = ft_strdup(argv[i]);
		if (!shell->tokens[i - 1])
		{
			free_tokens(shell->tokens);
			shell->tokens = NULL;
		}
		i++;
	}
	return (true);
}
