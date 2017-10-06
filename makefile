all:
	test -e build || mkdir build
	test -e bin || mkdir bin
	g++ -std=c++11 -I include -o bin/TestVector src/main.cpp

test:
	test -e build || mkdir build
	test -e bin || mkdir bin
	make test_libmatrix.o
	g++ -std=c++11 -I include build/test_libmatrix.o -o bin/test_libmatrix

test_libmatrix.o: test/test_libmatrix.cpp include/unit_test.h
	g++ -std=c++11 -I include test/test_libmatrix.cpp -o build/test_libmatrix.o 