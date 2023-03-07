```shell
for u in bob joe ; do
	echo $u
done
exit 0
```

```shell
for n in $*
do
	echo "Hello $n"
done
exit 0
```