```sh
git submodule add <repo link>
git diff --cached --submodule
git submodule init # init local config file
git submodule update # to fetch all data
git clone --recurse-submodules <repo link>
git submodule update --init # if cloned and not fetch
git submodule update --init --recursive
git submodule update --remote <name>
```