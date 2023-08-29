/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:02:40 by pcazac            #+#    #+#             */
/*   Updated: 2023/08/29 14:06:57 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Creates the token depending on the type and adds it to the AST
/// @param instr The pointer to the instruction
/// @param tree The tree structure to be filled
/// @return The length of the instruction
t_cmd	*pipe_token(t_cmd **tree)
{
	t_pipe	*node;
	int		i;

	i = 0;
	node = ft_calloc(1, sizeof(t_pipe));
	if (!node)
		ft_error("Allocation error", GENERAL_ERROR);
	node->type = NODE_PIPE;
	node->left = NULL;
	node->right = NULL;
	arrange_pipe_tree(tree, node);
	ft_printf("Type: %i\n", node->type);
	return ((t_cmd *)node);
}

/// @brief Creates, initializes and returns a redirect node for the AST
/// @param root Pointer to the command position
/// @return The pointer to the node
int		redirect_token(char *instr, t_cmd **tree)
{
	t_redir	*node;
	t_word	word;
	int		i;

	node = ft_calloc(1, sizeof(t_redir));
	if (!node)
		ft_error("Allocation error", GENERAL_ERROR);
	i = end_expression(instr, &word);
	node->type = NODE_REDIRECT;
	node->cmd = NULL;
	node->file = word.start;
	node->efile = word.end;
	node->mode = redirect_type(instr);
	node->fd = 0;
	ft_printf("Type: %i\n", node->type);
	arrange_redir_tree(tree, node);
	return (i);
}

/// @brief Creates, initializes and returns a command node for the AST
/// @param root Pointer to the command position
/// @return The pointer to the node
int		command_token(char **start, char **end, t_cmd **tree)
{
	t_exec	*node;
	int		i;

	i = 0;
	node = ft_calloc(1, sizeof(t_exec));
	if (!node)
		ft_error("Allocation error", GENERAL_ERROR);
	node->type = NODE_EXEC;
	node->cmd = start[0];
	node->argv = start;
	node->eargv = end;
	node->env = NULL;
	ft_printf("Type: %i\n", node->type);
	arrange_command_tree(tree, node);
	return (i);
}
