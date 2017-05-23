/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreeadd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:37:50 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 22:43:38 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dstruct/ftbtree.h>

void	ft_btreeadd(t_btree **head, void *content, int (*f)())
{
	t_btree	**tmp;

	if (!*head)
		*head = ft_btreenew(content);
	else
	{
		while (1)
		{
			if (f(content, (*head)->content) < 0)
				tmp = &((*head)->lnode);
			else
				tmp = &((*head)->rnode);
			if (!*tmp)
			{
				*tmp = ft_btreenew(content);
				(*tmp)->parent = *head;
				break ;
			}
			head = tmp;
		}
	}
}
