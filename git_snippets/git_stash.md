```shell
git stash # save temp work in progress WIP w/o commit
git stash save "message" # save local to new stash
git stash list # list stored stashes
git stash apply # apply the newest
git stash apply stask@{2} # apply older stash
git stash apply --index # try to reapply the stages
git stash pop # restore recently
git stash show # show the changes
git stash drop # discard recently
git stash drop stash@{2} # discard specific
git stash --keep-index # store only unstaged -> to commit staged
git stash -u # stash even untracked files
git stash show -p | git apply -R
git stash show -p stash@{2} | git apply -R
git stash branch <branch_name> # create a branch w/ the stash
```