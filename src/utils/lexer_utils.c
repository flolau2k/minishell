/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:02:40 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/15 08:27:51 by pcazac           ###   ########.fr       */
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

/// @brief Creates a linked list with each of the arguments
/// @param instr input argument
/// @return linked list pointer to the unprocessed tokens
int	get_word(t_word *word, t_word block, int i, bool *flag)
{
	int		cts;

	while (block.start[i] && ft_isspace(block.start[i]))
		i++;
	cts = i;
	if (ft_strchr("\'\"", block.start[i]))
		*flag = true;
	while (block.start[i] && block.start + i <= block.end)
	{
		if (*flag && inside_quotes(block.start[i]) )
		{
			word->start = &(block.start[cts]);
			word->end = &(block.start[i]);
			return (++i);
		}
		else if(!*flag && (ft_strchr("\'\"|<>", block.start[i]) || ft_isspace(block.start[i])))
		{
			word->start = &(block.start[cts]);
			word->end = &(block.start[i]);
			return (i);
		}
		i++;
		if (!block.start[i])
		{
			word->start = &(block.start[cts]);
			word->end = &(block.start[i]);
			return (i);
		}
	}
	return (0);
}

/// @brief Searches for the end of the expression and splits the args
/// @param instr Arguments from the command line
/// @return Returns the pointer to the end of the expression
void	get_args(t_array *array, t_word block, int i, int count)
{
	t_word	word;
	bool	flag;

	flag = false;
	word = (t_word){};
	i = get_word(&word, block, i, &flag);
	if (i == 0)
		return ;
	count++;
	if (block.start + i < block.end)
		get_args(array, block, i, count);
	if (block.start + i == block.end && !array->start && !array->end)
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
	else if (block.start + i == block.end)
		count = new_arr(array, count);
	ft_printf("#%s#\n", word.start);
	(array->start)[count - 1] = word.start;
	(array->end)[count - 1] = word.end;
	(array->flag)[count - 1] = flag;
	count--;
}

/// @brief Searches for the end of the expression
/// @param instr Arguments from the command line
/// @return Returns the pointer to the end of the expression
int	end_expression(char *instr, t_word *word)
{
	int	i;

	i = 0;
	while (instr[i] && ft_strchr(R_CHAR, instr[i]) && i < 2)
		i++;
	while (instr[i] && ft_isspace(instr[i]))
		i++;
	word->start = instr + i;
	while (instr[i] && !ft_strchr(P_CHAR, instr[i]) && !ft_isspace(instr[i]))
		i++;
	word->end = instr + i;
	return (i);
}
