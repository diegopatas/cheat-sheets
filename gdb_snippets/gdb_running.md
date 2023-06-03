```bash
run arglist # start your program with arglist
run         # start your program with current argument list
run ...<inf>outf # start your program with input, output redirected
kill      # kill running program
tty dev   # use dev as stdin and stdout for next run
set args arglist # specify arglist for next run
set args  # specify empty argument list
show args # display argument list
show env  # show all environment variables
show env var       # show value of environment variable var
set env var string # set environment variable var
unset env var      # remove var from environment
```