/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:07:41 by flauer            #+#    #+#             */
/*   Updated: 2023/08/21 11:11:48 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_shell
{
	char	**env;
	char	**tokens;
}	t_shell;

typedef enum
{
	NODE_CMD,
	NODE_PIPE
}	t_NodeType;

typedef struct s_ASTNode
{
	t_NodeType			type;
	void				*content;
	struct s_ASTNode	*left;
	struct s_ASTNode	*right;
}	t_ASTNode;

#endif