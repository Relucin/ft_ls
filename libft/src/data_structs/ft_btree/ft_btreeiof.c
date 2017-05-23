/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreeiof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 19:13:00 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 22:44:07 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dstruct/ftbtree.h>
#include <stdlib.h>

void	ft_btreeiof(t_btree *head, void (*f)())
{
	if (head)
	{
		ft_btreeiof(head->lnode, f);
		head->lnode = 0;
		f(head->content);
		ft_btreeiof(head->rnode, f);
		head->rnode = 0;
		free(head);
	}
}
