/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:40:14 by marvin            #+#    #+#             */
/*   Updated: 2023/09/17 19:28:07 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Function determines the type of redirect
/// @param instr Arguments from the command line
/// @return Returns te type
int	redirect_type(char *instr)
{
	if (instr[0] == '>' && instr[1] == '>')
		return (O_WRONLY | O_CREAT | O_APPEND);
	else if (instr[0] == '<' && instr[1] == '<')
		return (O_HEREDOC);
	else if (instr[0] == '>')
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (instr[0] == '<')
		return (O_RDONLY);
	return (0);
}

int	set_flag(char *array, int *i, int *offset)
{
	if (array[*i] && ft_strchr("\'", array[*i]))
	{
		while (ft_strchr("\'", array[*i]))
		{
			(*i)++;
			(*offset)++;
		}
		(*i)--;
		return (2);
	}
	else if (array[*i] && ft_strchr("\"", array[*i]))
	{
		while (ft_strchr("\"", array[*i]))
		{
			(*i)++;
			(*offset)++;
		}
		(*i)--;
		return (1);
	}
	else
		return (0);
}

void	allocate_array(t_array *array, int count)
{
	array->start = ft_calloc(count + 1, sizeof(char *));
	if (!(array->start))
		ft_error("Allocation erorr", GENERAL_ERROR);
	array->end = ft_calloc(count + 1, sizeof(char *));
	if (!(array->end))
		ft_error("Allocation erorr", GENERAL_ERROR);
	array->flag = ft_calloc(count + 1, sizeof(bool));
	if (!(array->flag))
		ft_error("Allocation erorr", GENERAL_ERROR);
}

void	fill_array(t_array *array, t_word *word, int count, int flag)
{
	(array->start)[count - 1] = word->start;
	if (flag == 2)
		(array->flag)[count - 1] = false;
	else
		(array->flag)[count - 1] = true;
}

/// @brief Checks for the delimiter and special characters
/// @param c character passed from the argument string
/// @return True if it is the researched char, false if not
bool	inside_quotes(char c)
{
	static bool	is_dquotes;
	static bool	is_squotes;

	if (!is_dquotes && !is_squotes)
	{
		if (c == '"')
			is_dquotes = true;
		else if (c == '\'')
			is_squotes = true;
		else if (ft_isspace(c))
			return (true);
		else if (c == '|')
			return (true);
	}
	else if (is_squotes && c == '\'')
	{
		is_squotes = false;
		return (true);
	}
	else if (is_dquotes && c == '"')
	{
		is_dquotes = false;
		return (true);
	}
	return (false);
}
