```bash
gcc -g -Wall -Wextra -Werror main.c   
```

```shell
gdb <prog>    # inicializa o gdb ==> gdb a.out
kill          # encerra o prog em execução
quit          # Ctrl + d serve também!
run           # executa o prog do início ao fim, direto
next          # avança à próxima instrução
print <var>   # exibe o valor ==> print x, print str[0]
continue      # executa o prog até o próximo breakpoint
step          # entra no flow de uma função
backtrace     # exibe a stack do prog em determinado frame
refresh       # limpa os bugs da tela :D
# VERSÃO CURTOS
run
n
p <var>
c
s
bt
refresh
```