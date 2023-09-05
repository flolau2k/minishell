/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:52:21 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 16:46:58 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_fcn_p	get_builtin(t_exec *exec)
{
	int						i;
	static const char		*fcn_n[] = {"echo", "cd", "env", "exit", "export", 
		"pwd", "unset"};
	static const t_fcn_p	fcn_p[] = {&f_echo, &f_cd, &f_env, &f_exit, 
		&f_export, &f_pwd, &f_unset};

	i = 0;
	while (fcn_n[i])
	{
		if (ft_strncmp(fcn_n[i], exec->cmd, ft_strlen(fcn_n[i])) == 0)
			return (fcn_p[i]);
		i++;
	}
	return (NULL);
}
