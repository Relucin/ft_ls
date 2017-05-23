/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreermmin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 08:28:40 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/23 15:34:56 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dstruct/ftbtree.h>
#include <stdlib.h>

static void	ft_btreermminh(t_btree **head, t_btree *tmp)
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

void		*ft_btreermmin(t_btree **head)
{
	t_btree	*tmp;
	void	*ret;

	tmp = *head;
	while (tmp->lnode)
		tmp = tmp->lnode;
	ret = tmp->content;
	if (tmp->rnode)
		ft_btreermminh(head, tmp);
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
