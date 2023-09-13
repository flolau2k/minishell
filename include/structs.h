/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:07:41 by flauer            #+#    #+#             */
/*   Updated: 2023/09/13 16:52:42 by marvin           ###   ########.fr       */
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
	bool	*flag;
}	t_array;

typedef struct s_var
{
	char	*name;
	char	*val;
}	t_var;

typedef struct s_exec
{
	t_nodetype	type;
	char		*cmd;
	char		**argv;
	char		**eargv;
	bool		*flag;
	t_shell		*sh;
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
	bool		*flag;
	int			mode;
	int			fd;
	int			ttyin;
	int			ttyout;
}	t_redir;

typedef int			(*t_fcn_p)(t_exec *);
typedef struct stat	t_stat;

#endif