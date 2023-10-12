/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:02:40 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/12 11:57:10 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Creates the token depending on the type and adds it to the AST
/// @param instr The pointer to the instruction
/// @param tree The tree structure to be filled
/// @return The length of the instruction
bool	pipe_token(t_cmd **tree, t_shell *sh)
{
	t_pipe	*node;

	node = ft_calloc(1, sizeof(t_pipe));
	if (!node)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	node->type = NODE_PIPE;
	node->pid = -1;
	node->sh = sh;
	node->left = NULL;
	node->right = NULL;
	arrange_pipe_tree(tree, node);
	return ((t_cmd *)node);
}

/// @brief Creates, initializes and returns a redirect node for the AST
/// @param root Pointer to the command position
/// @return The pointer to the node
bool	redirect_token(t_list **elm, t_cmd **tree, t_shell *sh)
{
	t_redir	*node;
	t_token	*conts[2];

	if (!(*elm)->next)
		return (false);
	conts[0] = (t_token *)(*elm)->content;
	conts[1] = (t_token *)(*elm)->next->content;
	if (conts[1]->type != WORD)
		return (false);
	node = ft_calloc(1, sizeof(t_redir));
	if (!node)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	*node = (t_redir){};
	node->type = NODE_REDIRECT;
	node->pid = -1;
	node->sh = sh;
	if (conts[0]->type == DLESS)
		node->file = hd_parse(conts[1]->start, sh, conts[1]->heredoc);
	else
		node->file = ft_strdup(conts[1]->start);
	node->mode = redirect_type(conts[0]);
	node->ttyin = sh->ttyin;
	node->ttyout = sh->ttyout;
	arrange_redir_tree(tree, node);
	(*elm) = (*elm)->next->next;
	return (true);
}

/// @brief Creates, initializes and returns a command node for the AST
/// @param root Pointer to the command position
/// @return The pointer to the node
bool	command_token(char **argv, t_cmd **tree, t_shell *sh)
{
	t_exec	*node;

	if (!argv || !argv[0])
		return (false);
	node = ft_calloc(1, sizeof(t_exec));
	if (!node)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	node->type = NODE_EXEC;
	node->pid = -1;
	node->sh = sh;
	node->argv = argv;
	node->cmd = argv[0];
	node->pid = -1;
	arrange_command_tree(tree, node);
	return (true);
}
