```bash
users
last
who
w
sudo <user>
sudo su
sudo awk -F":" '{print $1 " "}' /etc/passwd
adduser <user_name>  # (outra opcao) useradd -m <user_name>

id -u <user>
groups <user>
id -g <user>
usermod -aG [group] [user]
usermod -l <newname_user> <oldname_user>
usermod -g <group_name> <user>  # usermod -g <group_num> <user>
userdel -r <user_name>
passwd

sudo awk -F":" '{print $1}' /etc/group
groupadd <name>
groupdel <name>
getent group <group>
groupmod # groupmod -n <new_name> <old_name>

groups <user>
id -g <user>
gpasswd -a <user> <group>
gpasswd -d <user> <group>
```
