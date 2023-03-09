```bash
test
test -e /etc/hosts   # test if a file is present or not
test -f /etc/hosts   # test if a regular file
test -f /etc/hosts -a -r /etc/hosts # -f is regular, -a AND, -r readable
[ -f /etc/hosts -a -r /etc/hosts ]  # alternative
```
```shell
test     # doesn't show anything
echo $?  # evaluates false (1) because test returns 1 without param
test <expression>
test ! <expression>
test <expression> -a <expression> # -a: and
test <expression> -o <expression> # -o: or
[ <expression> ]   # same as test <expression>
```