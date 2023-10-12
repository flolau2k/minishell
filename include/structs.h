/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:07:41 by flauer            #+#    #+#             */
/*   Updated: 2023/10/12 14:56:29 by pcazac           ###   ########.fr       */
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

typedef enum e_tokentype
{
	LESS,
	DLESS,
	GREATER,
	DGREATER,
	SQUOTE,
	DQUOTE,
	PIPE,
	WORD
}	t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*start;
	size_t		length;
	bool		flag;
	bool		heredoc;
}	t_token;

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;

struct s_cmd
{
	t_nodetype	type;
	pid_t		pid;
	t_shell		*sh;
};

struct s_shell
{
	char	**env;
	t_cmd	*root;
	t_list	*token;
	char	*line;
	int		ret;
	int		ttyin;
	int		ttyout;
	t_list	*tmp_files;
};

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
	pid_t		pid;
	t_shell		*sh;
	char		*cmd;
	char		**argv;
}	t_exec;

typedef struct s_pipe
{
	t_nodetype	type;
	pid_t		pid;
	t_shell		*sh;
	t_cmd		*left;
	t_cmd		*right;
}	t_pipe;

typedef struct s_redir
{
	t_nodetype	type;
	pid_t		pid;
	t_shell		*sh;
	t_cmd		*cmd;
	char		*file;
	int			mode;
	int			fd;
	int			ttyin;
	int			ttyout;
}	t_redir;

typedef int				(*t_fcn_p)(t_exec *);
typedef struct stat		t_stat;

#endif
