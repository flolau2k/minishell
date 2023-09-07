/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:01:15 by flauer            #+#    #+#             */
/*   Updated: 2023/09/07 14:13:19 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_handler(int signo)
{
	(void)signo;
	printf("\n");
	if (rl_line_buffer[0] == '\0') {
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
