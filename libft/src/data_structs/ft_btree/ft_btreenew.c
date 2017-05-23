/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreenew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:35:30 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 22:44:34 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dstruct/ftbtree.h>
#include <stdlib.h>

t_btree	*ft_btreenew(void *content)
{
	t_btree *head;

	head = malloc(sizeof(t_btree));
	head->parent = 0;
	head->rnode = 0;
	head->lnode = 0;
	head->content = content;
	return (head);
}
