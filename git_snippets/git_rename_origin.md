```shell
git clone <link> <dir> $$ cd <dir> # 
git remote rm origin
# git init then follow bellow
git remote add navio <url>
git fetch navio main
git branch -u navio/main main
git remote -v # list fetch and push
git fetch --all --prune
git remote set-head navio -a
```