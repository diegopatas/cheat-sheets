```bash
bash -v my_script.sh # debug
bash -x my_script.sh # debug
```

```bash
#!/bin/bash
set -x # debug inside script
echo "Starting debug."
set +x
echo "Ending debug."
exit 0       # add command
```
