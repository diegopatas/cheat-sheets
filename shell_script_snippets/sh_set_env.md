```shell
printenv
printenv HOME
mkdir $HOME/bin               # create dir
export PATH=$PATH:$HOME/bin   # export dir path
touch my_script.sh            # create script file
mv my_script $HOME/bin           # move script
chmod +x $HOME/bin/my_script.sh  # change permission
my_script.sh + <CR>              # run script
echo $?                          # evaluate execution
```
