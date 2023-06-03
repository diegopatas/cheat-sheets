```bash
gdb <a.out>  # 1) inicia o gdb
tui enable   # 2) habilita o modo "gráfico" que é bonitinho
list         # 3) exibe o código fonte do seu prog maroto
start        # 4) inicia o debugging e para na main com breakpoint default
gdb --quiet <a.out> -tui  # gdb -q <prog> -tui
start
```