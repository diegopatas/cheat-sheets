```bash
:[range]delete [x]     # Delete specified lines [into register x]
:[range]yank [x]       # Yank specified lines [into register x]
:[line]put [x]         # Put the text from register x after the specified line
:[range]copy {address} # Copy the specified lines to below the line specifiedby {address} 
:[range]move {address} # Move the specified lines to below the line specified by {address}
:[range]join           # Join the specified lines
:[range]normal {commands} # Execute Normal mode {commands} on each specified line
:[range]substitute/{pattern}/{string}/[flags] # Replace occurrences of {pattern} with {string} on each specified line
:[range]global/{pattern}/[cmd] # Execute the Ex command [cmd] on all specified lines where the {pattern} matches
```
