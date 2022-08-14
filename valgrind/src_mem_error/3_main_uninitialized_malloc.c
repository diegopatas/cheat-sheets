/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_uninitialized_malloc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:20:42 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/12 11:22:14 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/* Há um leak proposital no programa */

int	main(void)
{
	char	*string;
	char	*creator;

	string = "ricky and morty";
	/* A seguir nós alocamos memória para uma variável, mas não a iniciliazamos */
	creator = (char *)malloc(5 * sizeof(char));
	/* O uso da var creator na printf a seguir causa o uninitiliazed error */
	printf("Cartoon: %s\nCreated by: %s\n", string, creator);
	return (0);
}
