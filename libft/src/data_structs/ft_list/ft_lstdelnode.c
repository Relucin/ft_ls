/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelnode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:47:36 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:49:51 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dstruct/ftlist.h>
#include <stdlib.h>

void	ft_lstdelnode(t_list **head, t_list *node)
{
	t_list *tmp;

	if (*head == node)
		*head = (*head)->next;
	else
	{
		tmp = *head;
		while (tmp->next != 0 && tmp->next != node)
			tmp = tmp->next;
		if (tmp->next == 0)
			return ;
		tmp->next = tmp->next->next;
	}
	free(node);
}
