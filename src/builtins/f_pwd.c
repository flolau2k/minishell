/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:29 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 16:13:55 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	f_pwd(t_exec *cmd)
{
	char	*cwd;
	(void)cmd;

	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
	// free_exec(cmd);
}
