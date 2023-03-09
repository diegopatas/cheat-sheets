```bash
if [ ! $# -eq 2 ] ; then
	echo "Provide <name> and <grade>"
	exit 2
fi

case ${2^^} in   # ^^ capitalizes argv
	A) echo "$1 is awesome!"
	;;
	B) echo "$1 is good!"
	;;
	*) echo "We cannot evaluate the grade for $1 $2"
	;;
esac
exit 0
```
```bash
case <expression> in
case 1)
	statement1
	statement2
	;;
case 2)
	statements
	;;
*)               # this happens when there is no match; goes at the end always
	statements
	;;
esac
```