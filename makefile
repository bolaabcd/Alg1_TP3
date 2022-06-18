build:
	g++ tp3.cpp -O2 -std=c++17 -o tp3.out
dbg: tp3.out

tp3.out: tp3.cpp
	g++ tp3.cpp -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++17 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts -o tp3.out
