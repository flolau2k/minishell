/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:27:21 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 14:07:16 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief searches and adds the tokens to the AST
/// @param instr 
/// @param tree 
/// @return 
void	add_command(char *instr, t_cmd **tree)
{
	int		i;
	t_word	word;
	char	**start;
	char	**end;

	i = -1;
	word.start = NULL;
	word.end = NULL;
	start = NULL;
	end = NULL;
	while (instr[++i] && !ft_strchr(P_CHAR, instr[i]))
	{
		if (!ft_strchr(R_CHAR, instr[i]))
		{
			word.start = instr + i;
			while (instr[i] && instr[i] != '|' && !ft_strchr(R_CHAR, instr[i]))
				i++;
			word.end = instr + i;
			get_args(&start, &end, word);
		}
		if (ft_strchr(R_CHAR, instr[i]))
			i += redirect_token(&(instr[i]), tree);
	}
	command_token(start, end, tree);
}

/// @brief Searches first for a command then searches for a pipe or a redir
/// @param instr Arguments from the command line
/// @param tree The pointer to the tree
/// @param i Location on the argument string
/// @return Returns the pointer to the AST
void	get_tree(char *instr, t_cmd **tree, int i)
{
	int	j;
	t_cmd	*node;

	node = NULL;
	j = -1;
	while (instr[++j] && ft_strchr(P_CHAR, instr[j]))
	{
		if (ft_strchr(P_CHAR, instr[j]))
			node = pipe_token(tree);
	}
	add_command(&(instr[i]), tree);
	if (instr[i])
		get_tree(instr + i, &node, i);
	return ;
}

/// @brief Splits the function and arranges into a AST
/// @param instr Input argument
/// @return AST root node
t_cmd	*do_lexing(char *instr)
{
	// int		i;
	t_cmd	*tree;
	
	tree = NULL;
	// tree = ft_calloc (1, sizeof(t_cmd));
	// if (!tree)
	// 	ft_error("Allocation error", GENERAL_ERROR);
	get_tree(instr, &tree, 0);
	return (tree);
}
