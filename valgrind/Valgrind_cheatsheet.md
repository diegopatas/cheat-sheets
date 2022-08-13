---
Aliases: 
---
%%
> Tag: [[valgrind]]
> Type: #type/product/tech 
> Status: #status/check-in
> Previous: 
> Next: 

> Branches: 

%%

> Context: #issue/no-tag #issue/orphan #issue/no-type 

---
# Valgrind (Memcheck)
---
## Breve introdução

1. Esse material é introdutório e não exaustivo.
3. Ele acompanha os códigos fonte dos exemplos que estão disponíveis para download.
4. Esses códigos foram compilados usando `gcc -Wall -Wextra -Werro main.c`
5. Se você é cadete da 42SP e caso prefira, verifique com a comunidade onde achar o vídeo que gravamos sobre esse conteúdo.

## O que é o Valgrind?

O `valgrind` é na verdade um conjunto de ferramentas que inclui o Memcheck, Callgrind, entre outros. Nesse workaround vamos abordar o `memcheck`.

 
 O `memcheck` é uma ferramenta de detecção de erros de memória, como por exemplo leitura e escrita inválida de memória, leaks de memória dinamicamente alocada, etc.


## Cheatsheet

```bash
gcc -Wall -Wextra -Werror <meu_binario>
valgrind <meu_binario>
valgrind --tool=memcheck <meu_binario>
valgrind --leak-check=full <meu_binario>
valgrind --track-origins=yes <meu_binario>
valgrind --show-leak-kinds=all <meu_binario>
valgrind --tool=calgrind <your_program>
```

---
## Comandos básicos

Os comandos a seguir são equivalente e rodam o vanilla `valgrind`.


```bash
valgrind --tool=memcheck <meu_binário>
```

```bash
valgrind <meu_binário>
```

---
# Parte 1: erros de memória

---
## Antes de mais nada: a função `malloc` o perigo da alocação dinâmica de memória

A maior parte dos problemas e bugs de um programa relacionados à memória está relacionado a alocação dinâmica da mesma. 


O compilador consegue nos auxiliar na identificação de alguns problemas existentes na stack em tempo de compilação, mas nos dá carta branca para manipular a heap, e é aí que mora o perigo.


Tenhamos em mente que a função `malloc(3)` reserva um pedaço de memória na região da Heap e retorna um ponteiro que aponta para a primeira posição do bloco em questão. 


A função `free(3)` remove a reserva realizada pela `malloc(3)`, mas ainda assim estamos permitidos usar a variável que continha o endereço da região alocada e liberada.

---
## Tipos de erros detectados e como interpretá-los

### Lista de erros comuns

1. Invalid read/ invalid write.
2. Uninitialized values.
3. Uninitialized ou unaddressable values em system calls.
4. Double free.
5. Fishy value.

### Erro do tipo Invalid read/ invalid write

- Invalid Read: Ocorre quando você tenta acessar/ler uma memória a qual você não possui permissão.
- Invalid Write: Ocorre quando você tenta escrever/gravar em uma memória a qual você não possui permissão.

**Exemplo: INVALID READ**

- Programa: `1_main_invalid_read.c`.
- Problema: uma string foi alocada e inicializada, mas não foi alocado espaço suficiente para o abrigar o byte nulo, `\0`.	
- Lembre-se de compilar o programa e depois executar o `valgrind`.

```bash
gcc main_invalid_read.c
valgrind a.out
```

- Saída:

```bash
#
==31957== Invalid read of size 1    # <==== AQUI!
==31957==    at 0x48426B4: __strlen_sse2 (vg_replace_strmem.c:496)
==31957==    by 0x48DFD14: __vfprintf_internal (vfprintf-internal.c:1688)
==31957==    by 0x48C8D3E: printf (printf.c:33)
==31957==    by 0x1091AC: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
==31957==  Address 0x4a5c042 is 0 bytes after a block of size 2 alloc'd
==31957==    at 0x483C855: malloc (vg_replace_malloc.c:381)
==31957==    by 0x10917E: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
==31957== 
Value: 42 
#
```

- Solução: alocar mais espaço e atribuir o byte nulo, `\0`. 
- Veja os comentários no source code do programa `1_main_invalid_read_sol.c`.

### Vamos interpretar essa saída

**Leitura**

- A saída está em forma de pilha (stack), então a primeira função chamada pelo programa, que é a `main`, vem por último;
- Os endereços em hexadecimal indicam a variáveis envolvidas no B.O. (informação útil para ser usada no GDB);
- O número à esquerda na forma  `==numero==` é o ID do seu programa/ processo, isto é, o PID;
- A informação entre parênteses indica o arquivo e a linha por onde o problema passou, `(printf.c:33)`.
- O `valgrind` exibe o tamanho dos elementos que deram problema, então o `Invalid read of size 1` indica possivelmente o tipo da var problemática; nesse caso, provavelmente estamos lidando com um `char` que costuma ter `size` 1 por default no sistema. Se houver 2 logs na forma `Invalid read of size 1` quer dizer que 2 `char` independentes são a fonte do erro.

---
**Troubleshooting**

- Então um bom caminho seria olhar qual variável tentamos ler na função `printf`;
- Depois, verificar o que alocamos na função `malloc`;
- Por fim, avaliar como inicialização nossa variável problemática.
	- Temos o byte nulo? 
	- A quantidade de espaço foi alocada corretamente?

---
**Exemplo: INVALID WRITE**

- Programa: `2_main_invalid_write.c`.
- Problema: uma string foi alocada, mas não tem espaço suficiente para receber uma cópia de conteúdo de outra string maior.


```bash
gcc main_invalid_write.c
valgrind a.out
```

- Saída:

```bash 
#
==32987== Invalid write of size 1  # <==== AQUI!                                                                                                                
==32987==    at 0x10919D: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)                             
==32987==  Address 0x4a5c042 is 0 bytes after a block of size 2 alloc'd                                                                            
==32987==    at 0x483C855: malloc (vg_replace_malloc.c:381)                                                                                        
==32987==    by 0x10917E: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)                             
#
```

- Solução: alocar mais espaço para alocar todos os dados necessários.
- Veja os comentários no source code do programa `2_main_invalid_write_sol.c`.

---
### Erro do tipo Uninitialized

Lembre-se que, como vimos, erros do tipo invalid ocorrem geralmente quando alocamos e definimos uma variável, mas a memória alocada não foi suficiente para armazenar todos os dados necessários, então quando tentamos acessar a área adjacente de memória ocorrem os problemas.

- **Uninitialized error:** ocorre quando alocamos memória, mas não definimos/ atribuímos um valor para a variável alocada.

**Exemplo: UNINITIALIZED VALUE**

- Programa: `3_main_uninitialized_malloc.c`.
- Problema: a variável `creator` foi alocada, mas não inicializada.
- Saída:

```bash
#
==46475== Conditional jump or move depends on uninitialised value(s) # <== AQUI!
==46475==    at 0x48426A9: __strlen_sse2 (vg_replace_strmem.c:496)
==46475==    by 0x48DFD14: __vfprintf_internal (vfprintf-internal.c:1688)
==46475==    by 0x48C8D3E: printf (printf.c:33)
==46475==    by 0x1091A9: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
#
```

- Solução: inicializar a variável com algum valor adequado.
- Veja os comentários no source code do programa `3_main_uninitialized_malloc_sol.c`.

**Uninitialized value: EXEMPLO ONDE O COMPILADOR NOS AJUDA**

- No programa `3_main_uninitialized_gccflag.c` consta um exemplo onde usamos uma variável do tipo `int` sem inicializá-la, mas esse problema é identificado pelo compilador com o uso de flag. O mesmo não ocorre se usamos a função`malloc`.

- Para testar essa afirmação, faça:

```bash
gcc -Werror 3_main_uninitialized_gccflag.c
```

- Porém, se você não usar as flags de compilação, então vai observar um erro parecido.
- Então, usando a flag `--track-origins=yes` você é capaz de identificar que a sua variável problemática foi inicializada na área `stack` do seu programa.

```bash
gcc 3_main_uninitialized_gccflag.c
valgrind --track-origins=yes a.out
```

- Saída:

```bash
# 
==47699== Conditional jump or move depends on uninitialised value(s)                                                                            
==47699==    at 0x48DE958: __vfprintf_internal (vfprintf-internal.c:1687)                                                                          
==47699==    by 0x48C8D3E: printf (printf.c:33)                                                                                                    
==47699==    by 0x10917A: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)                             
==47699==  Uninitialised value was created by a stack allocation  # <==== AQUI!                                                                                 
==47699==    at 0x109149: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
# 
```

---
### Erros do tipo uninitialised or unaddressable values durante syscalls

- Syscall param write(buf) points to uninitialised byte(s)
	- Se você tentar passar um buffer como parâmetro para uma syscall, o valgrind irá verificar duas coisas:
	1. Se o ponteiro para o buffer encontra valores inicializados, 
	2. ou se o valor referenciado do buffer foi inicializado!

**Exemplo**

- Programa: `4_main_unaddressable.c`.
- Problema: usar o endereço de um buffer inteiro sem valores inicializados como parâmetro de uma syscall (também vale para cada índice).
- Saída:
	- repare que essa saída trata 2 erros simultaneamente.

```bash
#
==62738== Syscall param write(buf) points to uninitialised byte(s) # <==== AQUI!
==62738==    at 0x4975077: write (write.c:26)
==62738==    by 0x1091A6: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
==62738==  Address 0x4a5c040 is 0 bytes inside a block of size 24 alloc'd
==62738==    at 0x483C855: malloc (vg_replace_malloc.c:381)
==62738==    by 0x10917E: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
==62738== 
==62738== Syscall param exit_group(status) contains uninitialised byte(s) # <==== AQUI!
==62738==    at 0x494A146: _Exit (_exit.c:31)
==62738==    by 0x48AD9C1: __run_exit_handlers (exit.c:132)
==62738==    by 0x48ADA5F: exit (exit.c:139)
==62738==    by 0x488B089: (below main) (libc-start.c:342)
==62738== 
# 
```

- Solução: inicializar o buffer!
- Veja os comentários no source code do programa `4_main_unaddressable_sol.c`.

---
### Erro do tipo double free

- Invalid free() / delete / delete[] / realloc()
	- O entendimento desse erro é imediato: é inadequado liberar duas vezes uma mesma memória alocada ou liberar uma memória alocada a partir da segunda posição de memória do bloco alocado. Para entender essa segunda afirmação basta lembra que quando alocamos memória com a função `malloc` ela retorna um ponteiro para a primeira posição do bloco alocado.

**Exemplo: double free**

- Programa: `5_main_doublefree.c`.
- Problema: aplicamos duas vezes a função `free` sobre o mesmo bloco de memória alocado com a função `malloc`.
- Saída:

```bash
# 
==74645== Invalid free() / delete / delete[] / realloc() # <==== AQUI!
==74645==    at 0x483F0C3: free (vg_replace_malloc.c:872)
==74645==    by 0x1091F7: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
==74645==  Address 0x4a5c040 is 0 bytes inside a block of size 24 free'd
==74645==    at 0x483F0C3: free (vg_replace_malloc.c:872)
==74645==    by 0x1091EB: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
==74645==  Block was alloc'd at
==74645==    at 0x483C855: malloc (vg_replace_malloc.c:381)
==74645==    by 0x10919E: main (in /home/diego/main/2k_Projeto/2005_Git/42_school/42_Game/0_cheatsheet/valgrind/a.out)
==74645== 
# 
```

- Solução: eliminar a duplicação da função `free`.
- Veja os comentários no source code do programa `5_main_doublefree_sol.c`.

---
### (Curiosidade) Erro do tipo fishy

---
# Parte 2: leaks

## Funcionamento e interpretação

O Memcheck rastreia todos os ponteiros devolvidos a cada chamada da função `malloc(3)`, então quando o programa é encerrado a Memcheck consegue determinar quais desses ponteiros não foram liberados com a função `free(3)`.


Observe que um bloco de memória alocado pode ser acessado de duas formas. Uma é através do ponteiro que aponta para o início do bloco (starter-pointer), que é devolvido pela `malloc`, a outra é através de um ponteiro que aponta para algum endereço subsequente (possivelmente o mesmo) ao endereço inicial do bloco (interior-pointer).

Dito isso, vamos observar 4 tipos de leaks identificados na saída do valgrind, no LEAK SUMMARY.

**Exemplo:**

```
LEAK SUMMARY:
   definitely lost: 48 bytes in 3 blocks.
   indirectly lost: 32 bytes in 2 blocks.
     possibly lost: 96 bytes in 6 blocks.
   still reachable: 64 bytes in 4 blocks.
        suppressed: 0 bytes in 0 blocks.

```

- *Still reachable:* há starter-pointers apontando para os blocos antes do final do programa, ou seja, seriam passíveis de um free e fáceis de serem resolvidos.
- *Definitely lost:* não há ponteiros acessando o bloco, ou seja, nenhuma variável guarda o endereço do bloco, logo a função free não pode ser aplicada diretamente.
- *Indirectly lost:* quando há perdas indiretas de endereço. Ocorre quando um starter-pointer se perde e isso causa a perda de todos os ponteiros que dependiam do starter-pointer para serem acessados.
- *Possibly lost:* ocorre quando identifica-se algum interior-pointer ativo, ou seja, existe a possibilidade de um starter-pointer do programa estar perdido?


**Atenção:** o log não diz como, onde ou o porquê seu programa vazou, isso é contigo! E os mais perigosos vazamentos são os *definitely* e *possibly lost*.

## Comandos

O Comando a seguir detalha ainda mais o log dos vazamentos identificados. Você vai notar a diferença no HEAP SUMMARY

```bash
valgrind --leak-check=full <meu_binario>
```


Em conjunto com a flag `--leak-check` você pode usar a flag `--show-leak-kinds` para detalhar os leaks. As possíveis combinações seguem:

```bash
valgrind --leak-check=full --show-leak-kinds=all <meu_binario>
valgrind --leak-check=full --show-leak-kinds=none <meu_binario>
valgrind --leak-check=full --show-leak-kinds=definite <meu_binario>
valgrind --leak-check=full --show-leak-kinds=reacheable <meu_binario>
valgrind --leak-check=full --show-leak-kinds=indirect <meu_binario>
valgrind --leak-check=full --show-leak-kinds=possible <meu_binario>
valgrind --leak-check=full --show-leak-kinds=definite,possible <meu_binario>
```


---
The answer to this question affects the numbers printed in the `ERROR SUMMARY` line, and also the effect of the `--error-exitcode` option. First, a leak is only counted as a true "error" if `--leak-check=full` is specified. Then, the option `--errors-for-leak-kinds=<set>` controls the set of leak kinds to consider as errors. The default value is `--errors-for-leak-kinds=definite,possible`

---
`--leak-resolution=<low|med|high> [default: high]`

When doing leak checking, determines how willing Memcheck is to consider different backtraces to be the same for the purposes of merging multiple leaks into a single leak report. When set to `low`, only the first two entries need match. When `med`, four entries have to match. When `high`, all entries need to match.

For hardcore leak debugging, you probably want to use `--leak-resolution=high` together with `--num-callers=40` or some such large number.

Note that the `--leak-resolution` setting does not affect Memcheck's ability to find leaks. It only changes how the results are presented.

---
`--track-origins=<yes|no> [default: no]`

Controls whether Memcheck tracks the origin of uninitialised values. By default, it does not, which means that although it can tell you that an uninitialised value is being used in a dangerous way, it cannot tell you where the uninitialised value came from. This often makes it difficult to track down the root problem.

---

###### Reference

- Documentação:
	- [Memcheck: a memory error detector](https://valgrind.org/docs/manual/mc-manual.html#mc-manual.leaks)
- Livros:
	- 
- Vídeos:
	- [Using Valgrind: Free Tools for Memory Management and Debugging](https://www.youtube.com/watch?v=-VDiEe9hxC4&list=PLhaU2Dr9h_F2g3hBdtjPETI0cDp14AwVO&index=34)
	- []()
