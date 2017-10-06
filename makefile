all:
	test -e build || mkdir build
	test -e bin || mkdir bin
	g++ -std=c++11 -I include -o bin/TestVector src/main.cpp

tests:
	test -e build || mkdir build
	test -e bin || mkdir bin
	g++ -std=c++11 -g -I include test/test_libmatrix.cpp -o bin/test_libmatrix