dephuse: src/main.cpp src/source.cpp src/tokenize.cpp src/parse.cpp
	g++ -Isrc src/main.cpp src/source.cpp src/tokenize.cpp src/parse.cpp -o dephuse -mtune=generic -march=x86-64

clean:
	rm dephuse