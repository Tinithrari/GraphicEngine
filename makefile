all:
	test -e build || mkdir build
	test -e bin || mkdir bin
	g++ -std=c++11 -I include -o bin/TestVector src/main.cpp

tests: test/test_libmatrix.cpp test/MatrixTest.cpp
	test -e build || mkdir build
	test -e bin || mkdir bin
	g++ -std=c++11 -g -I include test/test_libmatrix.cpp -o bin/test_libmatrix
	g++ -std=c++11 -g -I include -I /usr/include/cppunit test/MatrixTest.cpp -o bin/MatrixTest -lcppunit
	g++ -std=c++11 -g -I include -I /usr/include/cppunit test/Object3DTest.cpp -o bin/Object3DTest -lcppunit
