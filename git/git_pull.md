```shell
git fetch origin HEAD
git merge HEAD
git pull  # is the same as git fetch origin HEAD && git merge HEAD
git pull navio main
git pull --rebase # rebase your local changes on top of them
git pull --no-commit # it won't automatically merge them
```