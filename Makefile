.PHONY: ALL clean

ALL : checker gen moser

checker : checker.cpp
	g++ -O2 -o $@ $<

gen : gen.cpp
	g++ -O2 -o $@ $<

moser : moser.cpp
	g++ -O2 -o $@ $<

clean :
	rm -f checker gen moser
	rm -f 1.cnf 1.out
