```shell
echo "$USER earns $4"  # allow var expand
echo '$USER earns $4'  # don't allow var expand
echo "$USER earns \$4" # skip w/ \
FILE="my file"
rm $FILE         # rm my file (2 param)
FILE1="my file"
rm "$FILE"       # rm "my file" (1 param)
# $ allows parameters expansion
```
