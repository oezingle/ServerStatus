

build:
	rm -r bin

	mkdir -p bin

	mkdir -p bin/static

	gcc -c src/ping.cpp -o bin/static/ping.o -lstdc++

	ar rcs bin/static/libping.a bin/static/ping.o

	gcc -c src/main.cpp -o bin/main.o

	gcc bin/main.o -o bin/main -Lbin/static -lcurl -lstdc++ -lping

	#setcap cap_net_raw+ep bin/main