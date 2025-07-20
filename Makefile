dephuse: src/main.cpp src/source.cpp
	g++ -Isrc src/main.cpp src/source.cpp -o dephuse -mtune=generic -march=x86-64

clean:
	rm dephuse