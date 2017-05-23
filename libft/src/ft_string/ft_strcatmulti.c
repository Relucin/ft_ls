/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcatmulti.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 02:44:34 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:40:26 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftstring.h>

void	ft_strcatmulti(char *s1, char *s2, size_t times)
{
	while (times)
	{
		ft_strcat(s1, s2);
		--times;
	}
}
