```shell
test     # doesn't show anything
echo $?  # evaluates false (1) because test returns 1 without param
test <expression>
test ! <expression>
test <expression> -a <expression> # -a: and
test <expression> -o <expression> # -o: or
[ <expression> ]   # same as test <expression>
```