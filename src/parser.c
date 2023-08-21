/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:54:59 by flauer            #+#    #+#             */
/*   Updated: 2023/08/21 18:39:30 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/// @brief Function creates the tree from the token array
/// @param str 
/// @return 
t_astnode	*make_tree(char **str)
{
		int	i;

	i = 0;
	while (str[i])
}

/// @brief Parsing the strings received from the lexer
/// @param str array of arguments
/// @return List of parsed nodes for the AST
t_astnode	*parser(char **str)
{
	// If it is the first in the string  and not a redirect
	// Command Token
	t_astnode	*tree;

	tree = make_tree(str);
	
}
