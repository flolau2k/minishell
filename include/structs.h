/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:07:41 by flauer            #+#    #+#             */
/*   Updated: 2023/08/21 17:26:07 by flauer           ###   ########.fr       */
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
	NODE_PIPE,
	NODE_REDIRECT
}	t_nodetype;

typedef struct s_astnode
{
	t_nodetype			type;
	char				*cmd;
	char				**argv;
	char				**env;
	struct s_astnode	*left;
	struct s_astnode	*right;
}	t_astnode;

#endif