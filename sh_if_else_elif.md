```bash
if [ $# -lt 2] ; then
	echo "Whatever"
elif [ -d $mydir ] ; then
	echo "Hey there"
else
	echo "That's life"
fi
```