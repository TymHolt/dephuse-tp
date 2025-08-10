src_files = src/main.cpp src/source.cpp src/tokenize/tokenize.cpp src/parse/parse.cpp src/parse/ast_nodes.cpp
dephuse: $(src_files)
	g++ -Isrc $(src_files) -o dephuse -mtune=generic -march=x86-64

clean:
	rm dephuse