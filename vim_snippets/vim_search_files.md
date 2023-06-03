 Search in multiple files

-   :vim\[grep\] /pattern/ {\`{file}\`} - search for pattern in multiple files

e.g. :vim\[grep\] /foo/ \*\*/\*

-   :cn\[ext\] - jump to the next match
-   :cp\[revious\] - jump to the previous match
-   :cope\[n\] - open a window containing the list of matches
-   :ccl\[ose\] - close the quickfix window

 # - alternate file name  
 \* - clipboard contents (X11 primary)  
 + - clipboard contents (X11 clipboard)  
 / - last search pattern  
 : - last command-line  
 . - last inserted text  
 \- - last small (less than a line) delete  
 \= - expression register  
 \_ - black hole register  