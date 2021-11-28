

build:
	@if [ -f 'bin' ]; then \
		rm -r bin; \
	fi

	mkdir -p bin/static/ping/
	mkdir -p bin/static/output/

	gcc -c src/ping/ping.cpp -o bin/static/ping/ping.o -lstdc++
	gcc -c src/ping/Server.cpp -o bin/static/ping/Server.o -lstdc++
	gcc -c src/ping/ServerList.cpp -o bin/static/ping/ServerList.o -lstdc++
	ar rcs bin/static/libping.a bin/static/ping/ping.o bin/static/ping/Server.o bin/static/ping/ServerList.o

	gcc -c src/outputs/output.cpp -o bin/static/output/output.o -lstdc++
	gcc -c src/outputs/terminal.cpp -o bin/static/output/terminal.o -lstdc++
	ar rsc bin/static/liboutputs.a bin/static/output/terminal.o bin/static/output/output.o

	gcc -c src/main.cpp -o bin/main.o
	gcc bin/main.o -o bin/main -Lbin/static -lcurl -lstdc++ -lping -loutputs