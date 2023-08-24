/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:59 by flauer            #+#    #+#             */
/*   Updated: 2023/08/24 14:43:14 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// @brief 
/// @param instr 
/// @return 
char *is_redirect(char *instr)
{
	
}

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

bool	init(t_shell *sh, int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	*sh = (t_shell){};
	sh->env = set_env(env, NULL);
	return (true);
}