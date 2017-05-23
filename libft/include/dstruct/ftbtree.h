/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftbtree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 22:40:56 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 22:43:32 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTBTREE_H
# define FTBTREE_H

typedef struct		s_btree
{
	struct s_btree	*parent;
	struct s_btree	*rnode;
	struct s_btree	*lnode;
	void			*content;
}					t_btree;

t_btree				*ft_btreenew(void *content);
void				ft_btreeadd(t_btree **h, void *c, int (*f)());
void				*ft_btreermmin(t_btree **head);
void				ft_btreeiof(t_btree *head, void (*f)());
#endif
