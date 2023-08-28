/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:07:41 by flauer            #+#    #+#             */
/*   Updated: 2023/08/28 17:43:34 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/include/libft.h"

# define O_HEREDOC 0x0008

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
}	t_shell;

typedef struct s_word
{
	char	*start;
	char	*end;
}	t_word;

typedef struct s_var
{
	char	*name;
	char	*val;
}	t_var;

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

typedef struct s_exec
{
	t_nodetype	type;
	char		*cmd;
	char		**argv;
	char		**eargv;
	char		**env;
}	t_exec;

#endif