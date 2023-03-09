```shell
for path in /home/mydir/*
do
	if [ -d "$path"]
	then
		echo "$path is a dir"
	elif [ -f "$path" ]
	then
		echo "$path is a file"
	fi
done
```