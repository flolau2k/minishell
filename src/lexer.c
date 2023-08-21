/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:27:21 by flauer            #+#    #+#             */
/*   Updated: 2023/08/21 18:36:30 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// 

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

/// @brief Splits the function into individual srtings for creating tokens
/// @param instr input argument
/// @return token array for the parsing 
char	**do_lexing(char *instr)
{
	char	**ret;
	t_list	*lst;
	t_list	*temp;
	int		len;
	int		i;

	i = 0;
	lst = create_linked_list(instr);
	temp = lst;
	len = ft_lstsize(lst);
	ret = malloc(sizeof(char *) * (len + 1));
	// if (!ret)
	// 	ft_error(NULL); // The passed pointer to be checked 
	ret[len] = 0;
	while (i < len)
	{
		ret[i] = ft_strdup(temp->content);
		temp = temp->next;
		i++;
	}
	ft_lstclear(&lst, free);
	return (ret);
}
