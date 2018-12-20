./gen > 1.cnf
./moser < 1.cnf > 1.out
cat 1.cnf 1.out | ./checker
