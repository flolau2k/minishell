/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:02:40 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/15 18:51:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Creates a linked list with each of the arguments
/// @param instr input argument
/// @return linked list pointer to the unprocessed tokens
int	get_word(t_word *word, t_word *block, int *i, int *flag)
{
	int		cts;
	int		count;

	count = 0;
	while (block->start[*i] && ft_isspace(block->start[*i]))
		(*i)++;
	cts = *i;
	*flag = set_flag(block->start[*i]);
	while (block->start[*i] && block->start + *i < block->end)
	{
		if (*flag != 0 && inside_quotes(block->start[*i]))
		{
			word->start = &block->start[cts];
			word->end = &block->start[*i];
			(*i)++;
			return (count);
		}
		else if(*flag == 0 && (ft_strchr("\'\"|<>", block->start[*i]) || \
				ft_isspace(block->start[*i])))
		{
			word->start = &block->start[cts];
			word->end = &block->start[*i];
			return (count);
		}
		else if(*flag == 0 && ft_strchr("\'\"|<>", block->start[*i + 1]))
		{
			word->start = &block->start[cts];
			word->end = &block->start[*i];
			(*i)++;
			return (count);
		}
		(*i)++;
		count++;
		if (!block->start[*i])
		{
			word->start = &block->start[cts];
			word->end = &block->start[*i];
			return (count);
		}
	}
	return (count);
}

/// @brief Searches for the end of the expression and splits the args
/// @param instr Arguments from the command line
/// @return Returns the pointer to the end of the expression
void	get_args(t_array *array, t_word *block, int *i, int count)
{
	t_word	word;
	int		flag;

	flag = 0;
	word = (t_word){};
	while (get_word(&word, block, i, &flag))
	{
		count++;
		if (!array->start && !array->end)
			allocate_array(array, count);
		else if (array->start && array->end)
			arr_add_back(array, count);
		fill_array(array, &word, count, flag);
	}
	return ;
}

/// @brief Searches for the end of the expression
/// @param instr Arguments from the command line
/// @return Returns the pointer to the end of the expression
int	end_expression(char *instr, t_array *array)
{
	int		i;
	int		start;
	t_word	word;

	word = (t_word){};
	i = 0;
	while (instr[i] && ((ft_strchr(R_CHAR, instr[i]) && i < 2) || ft_isspace(instr[i])))
		i++;
	start = i;
	while (instr[i] && !ft_strchr(S_CHAR, instr[i]) && !ft_isspace(instr[i]))
		i++;
	word.start = ft_substr(instr, start, i - start);
	word.end = word.start + (i - start);
	i = 0;
	get_args(array, &word, &i, 0);
	return (i);
}

void	join_array(t_array *array, char *file)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	while(array->start[++i])
	{
		if (temp)
			temp = array->start[i];
		else
		{
			if (file)
				free(file);
			file = ft_strjoin(array->start[i], temp);
			if (!file)
			{
				// ERROR MANAGEMENT
				ft_error("ALLOCATION ERROR", GENERAL_ERROR);
			}
			temp = file;
		}
	}
}
