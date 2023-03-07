```bash
test
test -e /etc/hosts   # test if a file is present or not
test -f /etc/hosts   # test if a regular file
test -f /etc/hosts -a -r /etc/hosts # -f is regular, -a AND, -r readable
[ -f /etc/hosts -a -r /etc/hosts ]  # alternative
```