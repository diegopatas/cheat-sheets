/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_main_uninitialized_malloc_sol.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:20:42 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/12 11:26:42 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*string;
	char	*creator;

	string = "ricky and morty";
	/* A seguir nós alocamos memória para uma variável, mas não a iniciliazamos */
	creator = (char *)malloc(5 * sizeof(char));
	creator = "Mickey";
	printf("Cartoon: %s\nCreated by: %s\n", string, creator);
// 	free(cartoon);
	return (0);
}
