linux: test.cpp
	cp ../cmake-build-debug/libjson.so ./libjson.so
	g++ test.cpp -o test -L. -ljson -g

mac: test.cpp
	cp ../cmake-build-debug/libjjson.dylib ./libjjson.dylib
	g++ test.cpp -o test -L. -ljjson -g -std=c++14

clean:
	rm test libjson.so
