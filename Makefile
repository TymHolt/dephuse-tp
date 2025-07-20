bake: src/main.c
	g++ -Isrc src/main -o dephuse -mtune=generic -march=x86-64

clean:
	rm dephuse