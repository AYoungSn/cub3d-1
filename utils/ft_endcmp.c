/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahnys <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 21:19:10 by ahnys             #+#    #+#             */
/*   Updated: 2021/04/01 21:30:06 by ahnys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_endcmp(char *str, char *s)
{
	int size;
	int	i;

	size = ft_strlen(str) - 1;
	i = ft_strlen(s) - 1;
	while (str[size] && s[i])
	{
		if (str[size--] != s[i--])
			return (0);
	}
	return (1);
}
