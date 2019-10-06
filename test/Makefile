linux: test.cpp
	cp ../cmake-build-debug/libjson.so ./libjson.so
	g++ test.cpp -o test -L. -ljson -g

clean:
	rm test libjson.so