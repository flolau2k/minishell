/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:27:21 by flauer            #+#    #+#             */
/*   Updated: 2023/08/24 17:29:05 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Divides the input string into blocks and outputs it to be parsed

// Runs along a string and divides the statements
// It will run along a statement and divide each compound
// It will send the divided statement and the to the parser to be recognized and tokenized


/// @brief Arranges the order of the instructions in a hierarchy tree
/// @param tree Pointer to the tree
void	arrange_tree(t_cmd *tree, t_cmd *node)
{
	// Arrange the tree
	
}

/// @brief Splits the function and arranges into a AST
/// @param instr Input argument
/// @param root Root node of the AST
/// @return AST root node
t_cmd	*do_lexing(char *instr, t_cmd *root)
{
	int		i;
	t_cmd	*tree;
	
	i = -1;
	tree = ft_calloc (1, sizeof(t_cmd));
	if (!tree)
		ft_error("Allocation error", GENERAL_ERROR);
	while (instr[++i])
	{
		if (ft_strchr(PIPE_CHAR, instr[i]))
			i += pipe_token(instr[i], tree);
		else if (ft_strchr(REDIR_CHAR, instr[i]))
			i += redirect_token(instr[i], tree);
		else
			i += command_token(instr[i], tree);
	}
	return (tree);
}

// /// @brief Checks for the delimiter and special characters
// /// @param c character passed from the argument string
// /// @return True if it is the researched char, false if not
// static bool	check_char(char c)
// {
// 	static bool	is_dquotes;
// 	static bool	is_squotes;

// 	if (!is_dquotes && !is_squotes)
// 	{
// 		if (c == '"')
// 			is_dquotes = true;
// 		else if (c == '\'')
// 			is_squotes = true;
// 		else if (c == ' ')
// 			return (true);
// 	}
// 	else if (is_squotes && c == '\'')
// 		is_squotes = false;
// 		is_dquotes = false;
// 	return (false);
// }
