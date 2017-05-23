/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreermmin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 08:28:40 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 22:45:05 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dstruct/ftbtree.h>
#include <stdlib.h>

void	*ft_btreermmin(t_btree **head)
{
	t_btree	*tmp;
	void	*ret;

	tmp = *head;
	while (tmp->lnode)
		tmp = tmp->lnode;
	ret = tmp->content;
	if (tmp->rnode)
	{
		if (tmp->parent)
		{
			tmp->rnode->parent = tmp->parent;
			tmp->parent->lnode = tmp->rnode;
		}
		else
		{
			*head = tmp->rnode;
			tmp->rnode->parent = 0;
		}
	}
	else
	{
		if (tmp->parent)
			tmp->parent->lnode = 0;
		else
			*head = 0;
	}
	free(tmp);
	return (ret);
}
