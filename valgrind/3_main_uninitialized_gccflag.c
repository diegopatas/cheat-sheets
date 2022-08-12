/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_uninitialized_gccflag.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz <ddiniz@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:20:42 by ddiniz            #+#    #+#             */
/*   Updated: 2022/08/12 11:17:18 by ddiniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/* Se você compilar esse programa com gcc -Werror irá verificar que ele
 * identifica o problema de uninitialized error */

int	main(void)
{
	int		year;
	char	*string;

	string = "ricky and morty";
	printf("Pastelão: %s\nCreated in: %d\n", string, year);
	return (0);
}
