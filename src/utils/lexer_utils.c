/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:02:40 by pcazac            #+#    #+#             */
/*   Updated: 2023/08/25 19:41:50 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Searches for the end of the expression and splits the args
/// @param instr Arguments from the command line
/// @return Returns the pointer to the end of the expression
void	get_args(char ***start, char ***end, char *instr, char *instr_end)
{
	static int	i;

	i = 0;
	while (instr[i] && )
	{
		
	}
}

// /// @brief It will split the arguments from the 
// /// @param start Pointer array of the start of each statement
// /// @param end Pointer array pointing to end of each statement
// void	split_args(char **start, char **end)
// {
// 	static int	i;

// 	i = 0;
// 	while ()
// }

/// @brief Function determines the type of redirect
/// @param instr Arguments from the command line
/// @return Returns te type
int	redirect_type(char *instr)
{
	if (instr[0] == '>' && instr[1] == '>')
		return (REDIR_APPEND);
	else if (instr[0] == '<' && instr[1] == '<')
		return (REDIR_HEREDOC);
	else if (instr[0] == '>')
		return (REDIR_OUTPUT);
	else if (instr[0] == '<')
		return (REDIR_INPUT);
}

/// @brief Searches for the end of the expression
/// @param instr Arguments from the command line
/// @return Returns the pointer to the end of the expression
char	*end_expression(char *instr)
{
	int	i;

	i = 0;
	while (instr[i] && ft_strchr(R_CHAR, instr[i]) && i < 2)
		i++;
	while (instr[i] && instr[i] == ' ')
		i++;
	while (instr[i] && !ft_strchr(S_CHAR, instr[i]) && instr[i] != ' ')
		i++;
	return (instr + i);
}

/// @brief Arranges the order of the instructions in a hierarchy tree
/// @param tree Pointer to the tree
void	arrange_tree(t_cmd **tree, void *node)
{
	// Arrange the tree
	
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
		else if (c == ' ')
			return (true);
	}
	else if (is_squotes && c == '\'')
		is_squotes = false;
		is_dquotes = false;
	return (false);
}

/// @brief Creates a linked list with each of the arguments
/// @param instr input argument
/// @return linked list pointer to the unprocessed tokens
t_list	*create_linked_list(char *instr)
{
	t_list	*ret;
	int	i;
	int	cts;

	i = 0;
	cts = 0;
	ret = NULL;
	while (instr[i])
	{
		if (check_char(instr[i]))
		{
			ft_lstadd_back(&ret, ft_lstnew(ft_substr(instr, cts, i - cts)));
			cts = i + 1;
		}
		i++;
	}
	ft_lstadd_back(&ret, ft_lstnew(ft_substr(instr, cts, i - cts)));
	return (ret);
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
