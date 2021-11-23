

build:
	rm -r bin

	mkdir -p bin

	mkdir -p bin/static

	gcc -c src/ping/ping.cpp -o bin/static/ping.o -lstdc++
	gcc -c src/ping/Server.cpp -o bin/static/Server.o -lstdc++

	ar rcs bin/static/libping.a bin/static/ping.o bin/static/Server.o

	gcc -c src/main.cpp -o bin/main.o

	gcc bin/main.o -o bin/main -Lbin/static -lcurl -lstdc++ -lping