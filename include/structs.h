/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:07:41 by flauer            #+#    #+#             */
/*   Updated: 2023/08/22 12:03:24 by pcazac           ###   ########.fr       */
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

typedef enum
{
	NODE_EXEC,
	NODE_PIPE,
	NODE_REDIRECT
}	t_nodetype;

typedef struct s_cmd
{
	t_nodetype	type;
}	t_cmd;

typedef struct s_exec
{
	t_nodetype	type;
	char		*cmd;
	char		**argv;
	char		**eargv;
	char		**env;
}	t_exec;

typedef struct s_pipe
{
	t_nodetype	type;
	t_cmd		*left;
	t_cmd		*right;
}	t_pipe;

typedef struct s_redir
{
	t_nodetype	type;
	t_cmd		*cmd;
	char		*file;
	char		*efile;
	int			mode;
	int			fd;
}	t_redir;

#endif