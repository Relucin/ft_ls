/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:01:05 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:51:45 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>
#include <dstruct/ftlist.h>
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *ntl;

	if (!(ntl = malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		if (!(ntl->content = malloc(content_size)))
			return (NULL);
		ft_memcpy(ntl->content, content, content_size);
		ntl->content_size = content_size;
	}
	else
	{
		ntl->content = NULL;
		ntl->content_size = 0;
	}
	ntl->next = NULL;
	return (ntl);
}
