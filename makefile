all:
	test -e build || mkdir build
	test -e bin || mkdir bin	
	g++ -std=c++11 -I include -o bin/TestVector src/main.cpp

benchmark:
	g++ -std=c++11 -g -I include -o bin/BenchmarkMatrix test/benchmark.cpp
	