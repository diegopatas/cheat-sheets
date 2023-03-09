
```shell
#!/bin/bash
RED="\033[31m" 
GREEN="\033[32m"
BLUE="\033[34m"
RESET="\033[30m"
```

```bash
#!/bin/bash
# Example script
source $HOME/snippets/shell_colors
echo -e "${RED}Error$RESET"   # -e can display colors
exit 0
```