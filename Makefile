# Пример команд сборки (Makefile)
all:
	g++ -c -fPIC fileops.cpp -o fileops.o 
	g++ -shared -o libfileops.so fileops.o
	g++ -c -fPIC rsa.cpp -o rsa.o
	g++ -shared -o librsa.so rsa.o
	g++ -c -fPIC double_change.cpp -o double_change.o
	g++ -shared -o libdouble_change.so double_change.o
	g++ -c -fPIC polybian.cpp -o polybian.o
	g++ -shared -o libpolybian.so polybian.o
	g++ encryptorinator.cpp -L. -lfileops -lrsa -ldouble_change -lpolybian -o encryptorinator
	LD_LIBRARY_PATH=. ./encryptorinator
