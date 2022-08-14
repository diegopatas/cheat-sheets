---
Aliases: 
---
%%
> Tag: [[valgrind]]
> Type: #type/product/tech 
> Status: #status/check-in
> Previous: [[Valgrind_cheatsheet_0_intro]]
> Next: [[]]

> Branches: 

%%

> Context: #issue/no-tag #issue/orphan #issue/no-type 

---
# Valgrind Parte 1: erros de memória

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
==31957==    by 0x1091AC: main (in ~/.../valgrind/a.out)
==31957==  Address 0x4a5c042 is 0 bytes after a block of size 2 alloc'd
==31957==    at 0x483C855: malloc (vg_replace_malloc.c:381)
==31957==    by 0x10917E: main (in ~/.../valgrind/a.out)
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
==32987==    at 0x10919D: main (in ~/.../valgrind/a.out)                             
==32987==  Address 0x4a5c042 is 0 bytes after a block of size 2 alloc'd                                                                            
==32987==    at 0x483C855: malloc (vg_replace_malloc.c:381)                                                                                        
==32987==    by 0x10917E: main (in ~/.../valgrind/a.out)                             
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
==46475==    by 0x1091A9: main (in ~/.../valgrind/a.out)
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
==47699==    by 0x10917A: main (in ~/.../valgrind/a.out)                             
==47699==  Uninitialised value was created by a stack allocation  # <==== AQUI!                                                                                 
==47699==    at 0x109149: main (in ~/.../valgrind/a.out)
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
	- repare que essa saída são duas partes do mesmo log.

```bash
#
==62738== Syscall param write(buf) points to uninitialised byte(s) # <==== AQUI!
==62738==    at 0x4975077: write (write.c:26)
==62738==    by 0x1091A6: main (in ~/.../valgrind/a.out)
==62738==  Address 0x4a5c040 is 0 bytes inside a block of size 24 alloc'd
==62738==    at 0x483C855: malloc (vg_replace_malloc.c:381)
==62738==    by 0x10917E: main (in ~/.../valgrind/a.out)
#
```

```
#
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
==74645==    by 0x1091F7: main (in ~/.../valgrind/a.out)
==74645==  Address 0x4a5c040 is 0 bytes inside a block of size 24 free'd
==74645==    at 0x483F0C3: free (vg_replace_malloc.c:872)
==74645==    by 0x1091EB: main (in ~/.../valgrind/a.out)
==74645==  Block was alloc'd at
==74645==    at 0x483C855: malloc (vg_replace_malloc.c:381)
==74645==    by 0x10919E: main (in ~/.../valgrind/a.out)
==74645== 
# 
```

- Solução: eliminar a duplicação da função `free`.
- Veja os comentários no source code do programa `5_main_doublefree_sol.c`.

---
### (Curiosidade) Erro do tipo fishy

---
