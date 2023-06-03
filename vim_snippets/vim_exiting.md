```bash
:w               # write (save) the file, but don't exit
:w !sudo tee %   # write out the current file using sudo
:wq              # write (save) and quit
:x               # write (save) and quit
ZZ               # write (save) and quit
:q               # quit (fails if there are unsaved changes)
:q! or ZQ        # quit and throw away unsaved changes
:wqa             # write (save) and quit on all tabs
```
