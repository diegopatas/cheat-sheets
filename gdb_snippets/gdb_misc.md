```bash
cd                # roda o comando cd direto do gdb
pwd               
make              # vale para make all, make clean, whatever
shell <command>   # exemplo: shell ls -la
info source       # lista a source da sessão
# Edita teu arquivo, salva
(gdb) make all
(gdb) file <a.out> # recarrega um binário
(gdb) source meu_script
(gdb) start
```