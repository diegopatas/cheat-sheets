---
Aliases: 
---
%%
> Tag: [[gdb]]
> Type: #type/product/tech 
> Status: #status/check-in
> Previous: 
> Next: 

> Branches: 

%%

> Context: #issue/no-tag #issue/orphan #issue/no-type 

---
# Workaround de GDB


---
## Compilação

**ATENCIÓN MIS AMIGOS!**

- Compile o seu programa com a flag `-g` ou `-g3` para você poder exibir o código fonte durante o debugging... (isso é bem importante!)

```bash
gcc -g -Wall -Wextra -Werror main.c   
```

## Essencial

```bash
# START/ QUIT
gdb <prog>   # inicializa o gdb ==> gdb a.out
kill          # encerra o prog em execução
quit          # Ctrl + d serve também!

# FLOW
run           # executa o prog do início ao fim, direto
next          # avança à próxima instrução
print <var>   # exibe o valor ==> print x, print str[0]
continue      # executa o prog até o próximo breakpoint
step          # entra no flow de uma função
backtrace     # exibe a stack do prog em determinado frame
refresh       # limpa os bugs da tela :D
```


```bash
# VERSÃO CURTOS
run
n
p <var>
c
s
bt
refresh
```


---
## Formas para iniciar o GDB

**Jeito 1) comando a comando**

```bash
# 1) inicia o gdb
gdb <prog>   

# 2) habilita o modo "gráfico" que é bonitinho
tui enable   

# 3) exibe o código fonte do seu prog maroto
list         

# 4) inicia o debugging e para na main com breakpoint default
start        

# 5) divirta-se
```

**Jeito 2) passando parâmetros (ótimo pra botar no Makefile, por exemplo)**

```bash
gdb --quiet <a.out> -tui  # gdb -q <prog> -tui
start
```


---
## Breakpoints

- Break points servem para você pausar a execução de seu programa em determinada linha ou função durante o debugging.
	- Útil para pular o flow sempre no mesmo lugar.
- Watch serve para você exibir o status de uma variável toda vez que o valor da sua variável mudar.
	- Útil para diminuir a quantidade de comandos para digitar.

```bash
# PARADAS
break <linha>              # exemplo: break 42
b main.c:42                # especifica o arquivo e a linha do mesmo
b <nome_da_função>         # exemplo: b ft_strlen
b main.c:ft_strjoin        
b +4                       # define break 4 linhas acima da linha atual
b -4                       # define break 4 linhas abaixo da linha atual
tbreak 42                  # breakpoint temporário

info break                 # exibe todos os breakpoint, por número
clear                      # limpa um breakpoint (jura? ¬¬)
clear main.c:42            
delete                     # deleta todos os breaks
delete <# break>           # deleta um break point pelo número
disable <# break>          # desabilita sem excluir
enable <# break>           # habilita de novo...
ignore <# break> <# vezes desejado> # ignora... (eu nem uso esse galera)

# WATCHES
info watch                 # exibe todos os watch, por número
watch <var>                # exemplo: watch str[4]
delete <# watch>           # exemplo: delete 42
disable <# watch>
enable <# watch>
```


---
## Controlando o fluxo de exec

- **Observação**
	- O comando `jump` é diferente do `break` pois o `jump` apenas pula para determinada linha, enquanto o `break` define um ponto de parada fixo onde o seu programa irá parar toda vez que você reiniciar o flow de debugging.

```bash
c
n
s
until                    
until ft_strlen          # pula para prox instrução/ função definida
finish                   # termina a execução da função 
return                   # retorna a função s/ executá-la até o final
jump <linha_no_escopo>   # exemplo: jump 42
```


---
## Display (print)

- **Adeus `printf`! (mentira, eu uso `printf` até hoje...)**

```bash
p <var>       # exemplo: print x, print str[0]
p /x str[0]   # printa str[0] no formato hexa...(sim, é um comando muito útil!)
p /d <var>    # x, d, u, o, t, f
```

**Prints automáticos...**

```bash
display <var>    # exibe o valor da var toda vez que o debug pausar
display /a <var> # exibe no formato pedido, tipo hexa, float etc.
display          # mostra todas as definidas

info display 
undisplay <func desejada>
disable disp <# desejado>
enable disp <# desejado>
```


---
## Stack

- Os comandos `backtrace` e `frame` são úteis para você a stack do seu programa e comparar com logs do valgrind! (**Modo caçador de bugs: ON**)

```bash
backtrace        # exibe toda pilha do seu programa em certo frame
backtrace <# >   # exibe a pilha de certo frame em diante
frame            # exibe o frame em contexto

bt               # versão curta de backtrace
```


---
## Scripts

- Aqui a criatividade e necessidade reinam!

1. Crie um arquivo

```bash
touch meu_script
```

1. Coloque comandos de gdb

```bash
start
break 42
break ft_strlen
watch x
watch size_total
...
```

1. Inicie o seu flow

```bash
gdb -q a.out -tui
```

1. Carregue o arquivo de script

```
source meu_script
```

- Fim!

- **Definindo seus próprios comandos**
	- Molde:

```
define <command>
	lista de comandos
end
```

- Exemplo:

```bash
define rr
	refresh
end
```

- Agora, após carregar o arquivo de script, você poderá usar o comando `rr` como um alias para o comando `refresh`.

- Você também poderia definir um pack para fazer um watch de variáveis.
- Exemplo:

```bash
define wv
	watch x
	watch str[0]
end
```

---
## Misc

```bash
# load bin
file <a.out>      # carrega um binário sem precisar reiniciar o gdb

# shell
cd                # roda o comando cd direto do gdb
pwd               
make              # vale para make all, make clean, whatever
shell <command>   # exemplo: shell ls -la

info source       # lista a source da sessão
```

- Algo muito útil:
	- Deixar o GDB aberto
	- Editar teu programa
	- Fazer o build no GDB e carregar o bin novo

```bash
# Edita teu arquivo, salva
(gdb) make all
(gdb) file a.out
(gdb) source meu_script
(gdb) start
```