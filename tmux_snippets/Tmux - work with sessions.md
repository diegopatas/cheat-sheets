---
Aliases: 
---
%%
> Tag: 
> Type: #
> Status: #status/check-in
> Previous: 
> Next: 

> Branches: 

%%

> Context: #issue/no-tag #issue/orphan #issue/no-type 

---
# Tmux - sessions workflow


```mermaid
flowchart TD
my([My favorite approach]) -->
open["`tmux`"] -->
restore["( +r )"] -->
cycling["Cycling +) or +("] -->
rename["Rename some session ( +$ )"] -->
save["( +s )"] -->
exit["`shutdown 0`"]

bash([Bash approach]) -->
list["`tmux ls`"] -->
exist{Exist?} -- Y ---> attach["`tmux attach -t <name>`"]
exist{Exist?} -- N --> new["`tmux new -s <name>`"]
exist -- Or ----> Kill
```

**Commands**

```bash
# my favorite
tmux
<prefix> + r
<prefix> + ( or + )
<prefix> + $
<prefix> + s

# bash approach
tmux ls
tmux new -s <session_name>
tmux attach -t <session_name>
tmux kill-session -t <session_name>

# tmux command line
: new
: new -s <name>
```