Ex 1.
Compile - `gcc -o ex1 ex1.c`
Run - `./ex1`
Get kill command - `pgrep -f ./ex1 | awk '{print "kill -s SIGUSR1 " $1}'`
Kill - `kill -s SIGUSR1 PID`

Ex 2.
Compile - `gcc -o ex2 ex2.c`
Run - `./ex2`
