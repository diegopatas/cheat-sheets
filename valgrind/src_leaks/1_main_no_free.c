/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 09:15:26 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/13 09:26:07 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	int	*array;
	int	index;

	array = (int *)malloc(100 * sizeof(int));
	index = 0;
	while (index < 100)
	{
		array[index] = index*index;
		index++;
	}
	printf("Spot 42: %d\n", array[42]);
	return (0);
}
