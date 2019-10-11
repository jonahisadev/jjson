linux: test.cpp
	cp ../cmake-build-debug/libjjson.so ./libjjson.so
	g++ test.cpp -o test -L. -ljjson -g

mac: test.cpp
	cp ../cmake-build-debug/libjjson.dylib ./libjjson.dylib
	g++ test.cpp -o test -L. -ljjson -g -std=c++14

clean:
	rm test libjjson.so libjjson.dylib
