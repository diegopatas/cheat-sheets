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
## Tmux - window workflow

```mermaid
flowchart TD

Where -- N --> Create["Create ( +c )"]
Where -- Y --> Cycling

Create -->
Rename["Rename ( +, )"] -->
Cycling -->
done{Done ?} -- Y --> Kill["Kill ( +& )"]
done{Done ?} -- N --> Continue

subgraph Where
	List["List ( +w )"]
	Find["Find ( +f )"]
end

subgraph Cycling
	Previous["Previous ( +p )"]
	Next[" Next ( +n )"]
end
```


**Commands**

```bash
<prefix>+w  # List
<prefix>+f  # Find 

<prefix>+c  # New 
<prefix>+,  # Rename
<prefix>+&  # Kill 

<prefix>+n  # Next
<prefix>+p  # Previous 
```