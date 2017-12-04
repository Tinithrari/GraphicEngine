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
	g++ -std=c++11 -g -I include -I /usr/include/cppunit test/TriangleTest.cpp -o bin/TriangleTest -lcppunit
	g++ -std=c++11 -g -I include -I /usr/include/cppunit test/PlaneTest.cpp -o bin/PlaneTest -lcppunit
	g++ -std=c++11 -g -I include -I /usr/include/cppunit test/QuaternionTest.cpp -o bin/QuaternionTest -lcppunit
	g++ -std=c++11 -g -I include -I /usr/include/cppunit test/TransformationTest.cpp -o bin/TransformationTest -lcppunit
	
clean:
	rm bin/*
