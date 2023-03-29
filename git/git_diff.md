```shell
git diff # diff not yet staged
git diff --cached # changes between the index and your last commit
git diff HEAD # changes in the working tree since your last commit
git diff --staged # diff staging and last ver
git diff topic main # show diff
git show <commit> # metadata for the commit
git diff --diff-filter=MRC # show only modification, rename, and copy
git diff --name-status # show only names and the nature of change
git diff -R # output diff in reverse
```