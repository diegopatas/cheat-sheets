```bash
vim *.c
:args                   # list all files
#args vs list
:args					#list args
:args {`file.name`}		#open
:args *.*
:args **/*.c			#find all .c in local and parent folder (accepts more globs)
:args **/*.*
:args **/*.c **/*.h
:args `ls .sources`     # run ls and consume output as args
:args `cat .header`
```