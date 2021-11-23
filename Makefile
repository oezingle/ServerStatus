

build:
	rm -r bin

	mkdir -p bin

	mkdir -p bin/static

	gcc -c src/ping/ping.cpp -o bin/static/ping.o -lstdc++
	gcc -c src/ping/Server.cpp -o bin/static/Server.o -lstdc++

	ar rcs bin/static/libping.a bin/static/ping.o bin/static/Server.o

	gcc -c src/outputs/output.cpp -o bin/static/output.o -lstdc++
	gcc -c src/outputs/terminal.cpp -o bin/static/terminal.o -lstdc++

	ar rsc bin/static/liboutputs.a bin/static/terminal.o bin/static/output.o

	gcc -c src/main.cpp -o bin/main.o

	gcc bin/main.o -o bin/main -Lbin/static -lcurl -lstdc++ -lping -loutputs