/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_main_scope.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:38:15 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/13 19:21:06 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	*create_mem(void)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char));
	return (ptr);
}

int	main(void)
{
	char	*ptr;

	ptr = create_mem();
	*ptr = 'p';
	printf("[Out]: %c\n", *ptr);
	free(ptr);
	return (0);
}
