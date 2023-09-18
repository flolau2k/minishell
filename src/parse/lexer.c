/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:27:21 by flauer            #+#    #+#             */
/*   Updated: 2023/09/18 09:41:52 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief searches and adds the tokens to the AST
/// @param instr 
/// @param tree 
/// @return 
void	add_command(t_shell *sh, char *instr, t_cmd **tree)
{
	int		i;
	int		c;
	t_word	word;
	t_array	array;

	i = 0;
	c = 0;
	word = (t_word){};
	array = (t_array){};
	while (instr[i] && instr[i] != '|')
	{
		while (instr[i] && ft_isspace(instr[i]))
			i++;
		if (instr[i] && !ft_strchr(R_CHAR, instr[i]))
		{
			word.start = instr + i;
			while (instr[i] && !ft_strchr(S_CHAR, instr[i]))
				i++;
			word.end = instr + i;
			get_args(&array, &word, &c, 0);
			if (!instr[i])
				break ;
		}
		if (instr[i] && ft_strchr(R_CHAR, instr[i]))
			i += redirect_token(&(instr[i]), tree, sh);
	}
	command_token(sh, &array, tree);
}

/// @brief Searches first for a command then searches for a pipe or a redir
/// @param instr Arguments from the command line
/// @param tree The pointer to the tree
/// @param i Location on the argument string
/// @return Returns the pointer to the AST
void	get_tree(t_shell *sh, char *instr, t_cmd **tree, int i)
{
	int	j;
	t_cmd	*node;

	node = NULL;
	j = i;
	while (instr[j] && instr[j] != '|')
		j++;
	add_command(sh, &(instr[i]), tree);
	if (instr[j] == '|')
	{
		node = pipe_token(tree);
		j++;
	}
	i = j;
	if (instr[j])
		get_tree(sh, instr, &node, j);
	return ;
}

/// @brief Splits the function and arranges into a AST
/// @param instr Input argument
/// @return AST root node
t_cmd	*do_lexing(t_shell *sh)
{
	t_cmd	*tree;

	tree = NULL;
	get_tree(sh, sh->line, &tree, 0);
	return (tree);
}
