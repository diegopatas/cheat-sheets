```shell
git branch # list all
git branch dev # create the dev branch
git checkout dev # switch to dev
git remote -v # list remote
git remote add origin <url> # add remote repo
git checkout -b main origin/main # create and track
git checkout --track origin/main # track
git branch -u origin/main # upstream
git branch --set-upstream-to origin/main # verbose
git branch -d dev # delete branch
git push origin --delete main # delete remote branch
```