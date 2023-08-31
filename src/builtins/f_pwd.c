/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:29 by flauer            #+#    #+#             */
/*   Updated: 2023/08/31 15:16:25 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	f_pwd(t_exec *cmd)
{
	char	*cwd;
	(void)cmd;

	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
	// free_exec(cmd);
}
