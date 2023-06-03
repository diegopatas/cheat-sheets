```bash
break <linha>         # exemplo: break 42
b main.c:42           # especifica o arquivo e a linha do mesmo
b <nome_da_função>    # exemplo: b ft_strlen
b main.c:ft_strjoin
b +4         # define break 4 linhas acima da linha atual
b -4         # define break 4 linhas abaixo da linha atual
tbreak 42    # breakpoint temporário
```
