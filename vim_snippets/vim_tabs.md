```bash
:tabe {filename}		#open file in a new tab
<C-w>T					#move current window to a new tab
:tabdo `cmd`      # run command on all tabs `:tabdo q`
gt
gT
:tabc #					#close
:tabo					#only current, close the others
:tabn {number id}		#go to
:tabn					#go to next
:tabp					#go to previous
:tabmove {0}			#move to the first spot

#normal mode
{number id}gt
:lcd {path}				#select path for the current window
:windo lcd {path}		#select path for all windows in a tab
```]