all:
	test -e build || mkdir build
	test -e bin || mkdir bin
	g++ -g  -std=c++11 -I include src/main.cpp -o bin/Scene3D  `sdl2-config --cflags --libs` -lSDL2_ttf

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
	g++ -std=c++11 -g -I include -I /usr/include/cppunit test/FrustumTest.cpp -o bin/FrustumTest -lcppunit
	
clean:
	rm bin/*
