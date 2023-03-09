```shell
# This will print the file content considering space
file="file.txt"
for var in $(cat $file)
do
	echo "$var"
done
```

```shell
file="file.txt"
IFS='\n'                 # here we change the default IFS to \n
for var in $(cat $file)
do
	echo "$var"
done
```