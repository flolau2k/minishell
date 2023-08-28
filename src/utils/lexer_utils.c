/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:02:40 by pcazac            #+#    #+#             */
/*   Updated: 2023/08/28 17:53:07 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Function determines the type of redirect
/// @param instr Arguments from the command line
/// @return Returns te type
int	redirect_type(char *instr)
{
	if (instr[0] == '>' && instr[1] == '>')
		return (O_APPEND);
	else if (instr[0] == '<' && instr[1] == '<')
		return (O_HEREDOC);
	else if (instr[0] == '>')
		return (O_WRONLY);
	else if (instr[0] == '<')
		return (O_RDONLY);
}

/// @brief Checks for the delimiter and special characters
/// @param c character passed from the argument string
/// @return True if it is the researched char, false if not
static bool	check_char(char c)
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
	}
	else if (is_squotes && c == '\'')
		is_squotes = false;
	else if (is_dquotes && c == '"')
		is_dquotes = false;
	return (false);
}

/// @brief Creates a linked list with each of the arguments
/// @param instr input argument
/// @return linked list pointer to the unprocessed tokens
int	get_word(t_word *word, t_word *block, int i)
{
	int		cts;

	while (block->start[i] && ft_isspace(block->start[i]))
		i++;
	cts = i;
	while (block->start[i])
	{
		if (check_char(block->start[i]))
		{
			word->start = block->start[cts];
			word->end = block->start[i];
			return (i);
		}
		i++;
	}
	return (0);
}

/// @brief Searches for the end of the expression and splits the args
/// @param instr Arguments from the command line
/// @return Returns the pointer to the end of the expression
void	get_args(char ***start, char ***end, t_word *block)
{
	static int	i;
	static int	count;
	t_word		word;

	i = 0;
	count = 0;
	while (block->start[i] && (block->start + i) < block->end)
	{
		i = get_word(&word, block, i);
		i++;
	}
	count++;
	if (word.end < block->end)
		get_args(start, end, block);
	if (word.end == block->end)
		*start = ft_calloc(count, sizeof(char *));
	if (!(*start))
		ft_error("Allocation erorr", GENERAL_ERROR);
	if (word.end == block->end)
		*end = ft_calloc(count, sizeof(char *));
	if (!(*end))
		ft_error("Allocation erorr", GENERAL_ERROR);
	*(start)[count] = word.start;
	*(end)[count] = word.end;
	count--;
}

// /// @brief Splits the function into individual srtings for creating tokens
// /// @param instr input argument
// /// @return token array for the parsing 
// char	**do_lexing(char *instr)
// {
// 	char	**ret;
// 	t_list	*lst;
// 	t_list	*temp;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	lst = create_linked_list(instr);
// 	temp = lst;
// 	len = ft_lstsize(lst);
// 	ret = malloc(sizeof(char *) * (len + 1));
// 	// if (!ret)
// 	// 	ft_error(NULL); // The passed pointer to be checked 
// 	ret[len] = 0;
// 	while (i < len)
// 	{
// 		ret[i] = ft_strdup(temp->content);
// 		temp = temp->next;
// 		i++;
// 	}
// 	ft_lstclear(&lst, free);
// 	return (ret);
// }

/// @brief Searches for the end of the expression
/// @param instr Arguments from the command line
/// @return Returns the pointer to the end of the expression
char	*end_expression(char *instr)
{
	int	i;

	i = 0;
	while (instr[i] && ft_strchr(R_CHAR, instr[i]) && i < 2)
		i++;
	while (instr[i] && ft_isspace(instr[i]))
		i++;
	while (instr[i] && !ft_strchr(S_CHAR, instr[i]) && !ft_isspace(instr[i]))
		i++;
	return (instr + i);
}

/// @brief Arranges the order of the instructions in a hierarchy tree
/// @param tree Pointer to the tree
void	arrange_tree(t_cmd **tree, void *node)
{
	// Arrange the tree
	
}
