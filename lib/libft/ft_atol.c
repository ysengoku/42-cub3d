/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 07:51:13 by yusengok          #+#    #+#             */
/*   Updated: 2024/02/20 07:51:22 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *s)
{
	int		i;
	long	sign;
	long	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
		nbr = nbr * 10 + (s[i++] - '0');
	return (nbr * sign);
}
