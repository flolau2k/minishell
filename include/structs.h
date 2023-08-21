/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:07:41 by flauer            #+#    #+#             */
/*   Updated: 2023/08/21 17:28:27 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCTS_H
# define STRUCTS_H

#include "../libft/include/libft.h"

typedef struct s_var
{
	char	*name;
	char	*val;
}	t_var;

typedef struct s_shell
{
	char	**env;
	char	**tokens;
	t_list	*vars;
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