/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:52:21 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 12:54:49 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static const char		*g_fcn_n[] = {
	"echo",
	"cd",
	"env",
	"exit",
	"export",
	"pwd",
	"unset"
};

static const t_fcn_p	g_fcn_p[] = {
	(t_fcn_p) & f_echo,
	(t_fcn_p) & f_cd,
	(t_fcn_p) & f_env,
	(t_fcn_p) & f_exit,
	(t_fcn_p) & f_export,
	(t_fcn_p) & f_pwd,
	(t_fcn_p) & f_unset
};

t_fcn_p	get_builtin(t_exec *exec)
{
	int	i;

	i = 0;
	while (g_fcn_n[i])
	{
		if (ft_strncmp(g_fcn_n[i], exec->cmd, ft_strlen(g_fcn_n[i])) == 0)
			return (g_fcn_p[i]);
		i++;
	}
	return (NULL);
}
