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
## Tmux - pane workflow


```mermaid
flowchart TD
Split -->
full["Full screen ( +z )"] -->
select["select pane by number ( +# )"] -->
toggle["Toggle last ( +; )"] -->
Cycling -->
kill["Kill ( +x)"]

subgraph Split
	vert["Veritcal ( +%)"]
	horiz["Horizontal ( +aspas)"]
end

subgraph Cycling
	swap["( +o)"]
	move["+{ or +}"]
	arrow["( +arrow key)"]
end

```


**Commands**

```bash
<prefix>+% # Split panes vertically
<prefix>+“ # Split panes horizontally
<prefix>+; # Toggle last active plane

<prefix>+x # Kill pane
<prefix>+q # Show pane numbers

# Cycling
<prefix>+o # Swap
<prefix>+{ # Move left
<prefix>+} # Move right
<prefix>+arrow key # Switching between panes
```