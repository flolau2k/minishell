/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:40:14 by pcazac            #+#    #+#             */
/*   Updated: 2023/10/10 11:42:51 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Function determines the type of redirect
/// @param instr Arguments from the command line
/// @return Returns te type
int	redirect_type(t_token *token)
{
	if (token->type == DGREATER)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else if (token->type == DLESS)
		return (O_RDONLY);
	else if (token->type == GREATER)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (token->type == LESS)
		return (O_RDONLY);
	return (0);
}
