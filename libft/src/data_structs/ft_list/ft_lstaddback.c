/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:56:26 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:48:43 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dstruct/ftlist.h>

void	ft_lstaddback(t_list **alst, t_list *new)
{
	t_list *thead;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	thead = *alst;
	while (thead->next)
		thead = thead->next;
	thead->next = new;
}
