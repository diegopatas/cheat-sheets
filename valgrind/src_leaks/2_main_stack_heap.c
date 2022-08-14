/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main_stack_heap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 11:22:21 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/13 16:32:12 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	*ft_return_var(void)
{
	int	number;
	int	*stack_ptr;

	number = 42;
	stack_ptr = &number;
	return (stack_ptr);
}

int	main(void)
{
	int	*caller;

	caller = ft_return_var();
	printf("What happen? ==> %d\n", *caller);
	return (0);
}
