# Vim - Marks

## Setting marks

To set a mark, type `m` followed by a letter. For example, `ma` sets mark **a** at the current position (line and column). If you set mark **a**, any mark in the current file that was previously identified as **a** is removed. If you set mark **A**, any previous mark **A** (in any file) is removed.

## Using marks

To jump to a mark enter an apostrophe (`'`) or backtick (`` ` ``) followed by a letter. Using an apostrophe jumps to the beginning of the line holding the mark, while a backtick jumps to the line and column of the mark.

Using a lowercase letter (for example `` `a ``) will only work if that mark exists in the current buffer. Using an uppercase letter (for example `` `A ``) will jump to the file and the position holding the mark (you do not need to open the file prior to jumping to the mark).

-   Each file can have mark **a** – use a lowercase mark to jump within a file.
-   There is only one file mark **A** – use an uppercase mark to jump between files.

| Command | Description |
| --- | --- |
| `ma` | set mark **a** at current cursor location |
| `'a` | jump to line of mark **a** (first non-blank character in line) |
| `` `a `` | jump to position (line and column) of mark **a** |
| `d'a` | delete from current line to line of mark **a** |
| ``d`a`` | delete from current cursor position to position of mark **a** |
| `c'a` | change text from current line to line of mark **a** |
| ``y`a`` | yank text to unnamed buffer from cursor to position of mark **a** |
| `:marks` | list all the current marks |
| `:marks aB` | list marks **a**, **B** |

Commands like `d'a` operate "linewise" and include the start and end lines.  
Commands like ``d`a`` operate "characterwise" and include the start but not the end character.

It is possible to navigate between lowercase marks:

| Command | Description |
| --- | --- |
| `]'` | jump to next line with a lowercase mark |
| `['` | jump to previous line with a lowercase mark |
| `` ]` `` | jump to next lowercase mark |
| `` [` `` | jump to previous lowercase mark |

The above commands take a count. For example, `` 5]` `` jumps to the fifth mark after the cursor.

## Special marks\[\]

Vim has some special marks which it sets automatically. Here are some of the most useful:

| Command | Description |
| --- | --- |
| `` `. `` | jump to position where last change occurred in current buffer |
| `` `" `` | jump to position where last exited current buffer |
| `` `0 `` | jump to position in last file edited (when exited Vim) |
| `` `1 `` | like `` `0 `` but the previous file (also `` `2 `` etc) |
| `''` | jump back (to line in current buffer where jumped from) |
| ` `` ` | jump back (to position in current buffer where jumped from) |
| `` `[ `` or `` `] `` | jump to beginning/end of previously changed or yanked text |
| `` `< `` or `` `> `` | jump to beginning/end of last visual selection |

See the full list at [:help '\[](http://vimdoc.sourceforge.net/cgi-bin/help?tag=%27%5B) and following.

## Deleting marks

If you delete a line containing a mark, the mark is also deleted.

If you wipeout a buffer (command `:bw`), all marks for the buffer are deleted.

The `:delmarks` command (abbreviated as `:delm`) may be used to delete specified marks.

| Command | Description |
| --- | --- |
| `:delmarks a` | delete mark **a** |
| `:delmarks a-d` | delete marks **a**, **b**, **c**, **d** |
| `:delmarks abxy` | delete marks **a**, **b**, **x**, **y** |
| `:delmarks aA` | delete marks **a**, **A** |
| `:delmarks!` | delete all lowercase marks for the current buffer (a-z) |

## References

-   [:help mark-motions](http://vimdoc.sourceforge.net/cgi-bin/help?tag=mark-motions)
## Marks and positions

-   :marks - list of marks
-   ma - set current position for mark A
-   \`a - jump to position of mark A
-   y\`a - yank text to position of mark A
-   \`0 - go to the position where Vim was previously exited
-   \`" - go to the position when last editing this file
-   \`. - go to the position of the last change in this file
-   \`\` - go to the position before the last jump
-   :ju\[mps\] - list of jumps
-   Ctrl + i - go to newer position in jump list
-   Ctrl + o - go to older position in jump list
-   :changes - list of changes
-   g, - go to newer position in change list
-   g; - go to older position in change list
-   Ctrl + \] - jump to the tag under cursor

**Tip** To jump to a mark you can either use a backtick (\`) or an apostrophe ('). Using an apostrophe jumps to the beginning (first non-blank) of the line holding the mark.
##

The `:delmarks` command requires Vim 7.0. On previous versions, a kludge to remove all marks is to enter the command `:%!cat` (on Unix-based systems), or `:%!type` (on Windows) to delete the entire contents of the buffer and replace each line with itself by filtering through an external command. A mark is automatically deleted when its line is deleted.

___

I suggest moving the **Deleting** section below the **Using** section. ([Spiiph](https://vim.fandom.com/wiki/User:Spiiph "User:Spiiph") 11:53, 30 July 2009 (UTC))

I was scratching my head wondering why I put them in their current order, but when I went to move it, I see why. It's nice that "Using" and "Special" can be seen together, on the same screen because they are the items that a reader will probably want to refer to (it's a bit hard to keep all of it in your mind). I suppose "Deleting" could go after "Special", but that might be as strange as where it is now? [JohnBeckett](https://vim.fandom.com/wiki/User:JohnBeckett "User:JohnBeckett") 23:34, 30 July 2009 (UTC)

I think that would be better, even though it might seem illogical. Another idea would be to remove the section on **Deleting marks** altogether. I don't think I have ever used that functionality, and users who need it are probably advanced enough to find the information in the `:help`. ([Spiiph](https://vim.fandom.com/wiki/User:Spiiph "User:Spiiph") 13:39, 2 August 2009 (UTC))

Done.