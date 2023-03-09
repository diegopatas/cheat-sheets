```shell
for f in * ; do
[ -d "$f" ] || continue
chmod +x "$f"
done
```

```shell
for dir in * ; do
[ -d "$dir" ] && break
done
echo "We found a directory $dir"
```
