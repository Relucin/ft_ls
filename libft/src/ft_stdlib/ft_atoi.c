/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 12:46:38 by bmontoya          #+#    #+#             */
/*   Updated: 2017/05/21 16:42:10 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftctype.h>

int			ft_atoi(const char *str)
{
	int						flag;
	int						count;
	unsigned long long int	val;

	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	flag = (*str == '-') ? -1 : 1;
	str += (flag == -1 || *str == '+') ? 1 : 0;
	while (*str == '0')
		str++;
	val = 0;
	count = 0;
	while (ft_isdigit(*str) && ++count)
		val = (val * 10ULL) + (*str++ - '0');
	if (count > 19 || val > 9223372036854775807UL)
		return (flag == -1) ? 0 : -1;
	return (val * flag);
}
