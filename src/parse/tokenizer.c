/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:02:40 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/15 15:06:31 by marvin           ###   ########.fr       */
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

	node = ft_calloc(1, sizeof(t_pipe));
	if (!node)
		ft_error("Allocation error", GENERAL_ERROR);
	node->type = NODE_PIPE;
	node->left = NULL;
	node->right = NULL;
	arrange_pipe_tree(tree, node);
	return ((t_cmd *)node);
}

/// @brief Creates, initializes and returns a redirect node for the AST
/// @param root Pointer to the command position
/// @return The pointer to the node
int		redirect_token(char *instr, t_cmd **tree)
{
	t_redir	*node;
	t_array	array;
	int		i;

	array = (t_array){};
	node = ft_calloc(1, sizeof(t_redir));
	if (!node)
		ft_error("Allocation error", GENERAL_ERROR);
	i = end_expression(instr, &array);
	node->type = NODE_REDIRECT;
	node->cmd = NULL;
	node->file = NULL;
	node->argv = array.start;
	node->eargv = array.end;
	node->flag = array.flag;
	node->mode = redirect_type(instr);
	node->fd = 0;
	arrange_redir_tree(tree, node);
	return (i);
}

/// @brief Creates, initializes and returns a command node for the AST
/// @param root Pointer to the command position
/// @return The pointer to the node
int		command_token(t_shell *sh, t_array *array, t_cmd **tree)
{
	t_exec	*node;
	int		i;

	if (!array->start && !array->end)
		return (*tree = NULL, 0);
	i = 0;
	node = ft_calloc(1, sizeof(t_exec));
	if (!node)
		ft_error("Allocation error", GENERAL_ERROR);
	node->type = NODE_EXEC;
	node->cmd = array->start[0];
	node->argv = array->start;
	node->eargv = array->end;
	node->flag = array->flag;
	node->sh = sh;
	arrange_command_tree(tree, node);
	return (i);
}
