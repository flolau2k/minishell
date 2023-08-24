/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/parse/parser.c
/*   Created: 2023/08/08 16:54:59 by flauer            #+#    #+#             */
/*   Updated: 2023/08/22 15:42:05 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/// @brief Function creates the tree from the token array
/// @param str 
/// @return 
void	*make_tree(char **str)
{
		int	i;

	i = 0;
	while (str[i])
}

/// @brief Parsing the strings received from the lexer
/// @param str array of arguments
/// @return List of parsed nodes for the AST
void	*parser(char **str)
{
	// If it is the first in the string  and not a redirect
	// Command Token
	void	*tree;
	char	**;

	l_blocks = 
	tree = make_tree(str);
=======
/*   Created: 2023/08/21 14:10:37 by flauer            #+#    #+#             */
/*   Updated: 2023/08/22 13:53:09 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	f_env(t_exec *cmd)
{
>>>>>>> origin/env_builtins:src/builtins/f_env.c
	
}
