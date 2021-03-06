/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 07:03:22 by jraffin           #+#    #+#             */
/*   Updated: 2021/04/12 08:01:27 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_intlen(int n)
{
	int		i;

	i = (n <= 0);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}
