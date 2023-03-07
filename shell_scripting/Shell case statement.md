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