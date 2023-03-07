```shell  
#!/bin/bash  
echo -n "Hello! Enter your name: "  
read # getting input with echo and read  
echo "hello $REPLY" # $REPLY env var
read -p "Enter your name: " name # -p getting input with read  
echo "hello $name" # echo user-defined var
# other uses of read command
read -n1 -p "Press any key to exit" # -n limit char number  
read -sn1 -p "Type any key to exit" # -s silent input  
```
