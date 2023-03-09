```bash
test $USER = root     # test equality
[ $USER = root ]      # other notation
test ! $USER = root   # test negation
[ ! $USER = root ]    
test -z $1            # test for a zero string
[ -z $1 ]
[ -n $1 ]             # test longer than zero
```