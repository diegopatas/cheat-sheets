```bash
# ON BASH
gdb -q -tui <a.out>
# ON GDB
source <script>
```

```bash
# ON BASH
touch gdbsc
# INSIDE gdbsc
start
break 42
break ft_strlen
watch x
watch size_total

define rr      # define <command>
	refresh    # 	lista de comandos
end            # end

define wv
	watch x
	watch str[0]
end
```