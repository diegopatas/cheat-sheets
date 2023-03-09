```bash
FILE="my file"
rm $FILE         # rm my file (2 param)
FILE1="my file"
rm "$FILE"       # rm "my file" (1 param)
# $ allows parameters expansion
```

```bash
FILE="my file"
[[ -f $FILE && -r $FILE ]] && cat "$FILE"  # [[ parses its arguments before bash expands them
```