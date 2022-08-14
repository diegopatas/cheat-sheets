/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_main_stack_heap_sol.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 11:22:21 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/13 16:28:00 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	*ft_return_var(void)
{
	int	*heap_ptr;

	heap_ptr = (int *)malloc(sizeof(int));
	*heap_ptr = 42;
	return (heap_ptr);
}

int	main(void)
{
	int	*caller;

	caller = ft_return_var();
	printf("What happen? ==> %d\n", *caller);
	free(caller);
	return (0);
}
