```shell
sudo apt install openssh-client openssh-server # install ssh
mkdir ~/.ssh # create dir
touch ~/.ssh/config # create config file
ssh-keygen -t ed25519 -C "your_email@example.com" # gen key
# don't add passphrases 
eval "$(ssh-agent -s)" # start agent
ssh-add ~/.ssh/id_ed25519.pub # add pair keys
cat ~/.ssh/id_ed25519.pub # output key
# copy that and past to your account
git clone <ssh_repo_link> # clone repo
```