```shell
# I could test a value and then set an alternative new value, or a I could set a substitution value directly 
# The default value is set whenever the variable has not been declare and has a null value
name=$1
[ -z $name ] && name="Ney Name"  # or
name=${1-"New Name"}             # ${param-default}
```