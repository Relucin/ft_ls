/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcrep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 23:11:03 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 23:11:21 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcrep(const char *str, char c)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			++count;
		++str;
	}
	return (count);
}
