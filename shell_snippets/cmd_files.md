```sh
ls # ls -la ~ ls -ltr
ls | xargs wc # Words/lines/bytes in directory
touch <file>
cat <file>
less <file> # q to quit
more <file> # q to quit
head <file>
tail <file> # tail -n 5 [file] ~ tail -f
sort <file> # sort -u ~ sort -n
file <file> # ASCII type
mkdir <name>
rm <file> # rm -r [directory] | rm -rf [directory]
cp <file1> <file2> # cp -r [directory1] [directory2]
mv <file1> <file2>
grep <string> <file>
pwd
ln -s </path/file> <link>
gpg -c <file>
gpg <file.gpg>
wc
cut -d<delimiter> <file>
<data> | cut -d<delimiter>
awk '<pattern> {print $0}' <file>
shred -u <file>
diff <file1> <file2>
source <file1>
<cmd> | tee <file> > /dev/null
```