/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:07:41 by flauer            #+#    #+#             */
/*   Updated: 2023/09/14 15:50:24 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_nodetype
{
	NODE_EXEC,
	NODE_PIPE,
	NODE_REDIRECT
}	t_nodetype;

typedef struct s_cmd
{
	t_nodetype	type;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	t_cmd	*root;
	char	*line;
	int		ret;
	int		ttyin;
	int		ttyout;
}	t_shell;

typedef struct s_word
{
	char	*start;
	char	*end;
}	t_word;

typedef struct s_array
{
	char	**start;
	char	**end;
}	t_array;

typedef struct s_var
{
	char	*name;
	char	*val;
}	t_var;

typedef struct s_exec
{
	t_nodetype	type;
	char		*cmd; // not allocated
	char		**argv; // elements allocated
	char		**eargv; // allocated 
	t_shell		*sh;
	pid_t		pid; //init with -1
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
	t_cmd		*cmd; // not allocated
	char		*file; // allocated
	char		*efile; // not allocated
	int			mode;
	int			fd;
	int			ttyin;
	int			ttyout;
}	t_redir;

typedef int			(*t_fcn_p)(t_exec *);
typedef struct stat	t_stat;

#endif