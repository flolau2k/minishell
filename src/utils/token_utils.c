/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:46:19 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/18 17:43:02 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**make_array(t_list **elm)
{
	t_token	*conts;
	char	**arr;
	char	*new;

	new = NULL;
	arr = NULL;
	conts = (t_token *)(*elm)->content;
	while ((*elm) && (conts->type == WORD || conts->type == DQUOTE
			|| conts->type == SQUOTE))
	{
		new = ft_strdup(conts->start);
		if (new)
		arr	= array_addback(arr, new);
		(*elm) = (*elm)->next;
		if (*elm)
			conts = (t_token *)(*elm)->content;
	}
	return (new);
}

char	**array_addback(char **arr, char *new)
{
	int		len;
	int		i;
	char	**ret;

	i = 0;
	if (!new)
		return (arr);
	len = array_len(arr) + 1;
	ret = ft_calloc((len + 1), sizeof(char *));
	if (!ret)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	while (i < len)
	{
		if (i == len - 1)
			ret[i] = ft_strdup(new);
		else
			ret[i] = ft_strdup(arr[i]);
		i++;
	}
	free_arr(arr);
	return (ret);
}
