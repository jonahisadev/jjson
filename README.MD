# JJSON (JSON Parser)

I built this simple JSON parser in a weekend. It probably works. I didn't want to bother learning
a JSON library, so instead of spending an hour or so on learning an existing implementation, I
spent a weekend building a crappy one. There is no documentation for this one other than the code.
One day I'll provide documentation. One day.

This was built entirely in C++ 14 using the STL. Compile your projects with `-std=c++14`.

## Installation

This has only been built and tested on Linux. The installation process
will be similar for MacOS. Windows sucks so I'll work on a solution for
that in the near future. Open up a terminal and get to this directory.
Run these commands:

```
mkdir build && cd build && cmake ..
make
sudo make install
```

This will build and install the library.

## Usage

Give test/test.cpp a gander, that's basically how you use it.