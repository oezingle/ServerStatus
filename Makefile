default:
	make json

	make build

dirs:
	@if [ -d 'bin' ]; then \
		rm -r bin; \
	fi

	mkdir -p bin/static/ping/
	mkdir -p bin/static/output/

build:
	make dirs 

	# Compile pinging utils
	gcc -c src/ping/ping.cpp -o bin/static/ping/ping.o
	gcc -c src/ping/Server.cpp -o bin/static/ping/Server.o
	gcc -c src/ping/ServerList.cpp -o bin/static/ping/ServerList.o
	ar rcs bin/static/libping.a bin/static/ping/ping.o bin/static/ping/Server.o bin/static/ping/ServerList.o

	# Compile output utils
	gcc -c src/outputs/output.cpp -o bin/static/output/output.o
	gcc -c src/outputs/terminal.cpp -o bin/static/output/terminal.o
	ar rsc bin/static/liboutputs.a bin/static/output/terminal.o bin/static/output/output.o

	# Compile config & main, link libraries
	gcc -c src/config.cpp -o bin/config.o
	gcc -c src/main.cpp -o bin/main.o
	gcc bin/main.o bin/config.o -o bin/main -Lbin/static -lstdc++ -lping -loutputs -lconfig -lboost_json

json:
	@if [ -d 'src/json' ]; then\
		rm -r src/json; \
	fi

	mkdir -p src/json
	
	# ports.json -> remove whitespace -> array of chars
	sed src/ports.json -z -e 's/\([^aA-zZ]\)\s*/\1/g' > src/json/port_defaults
	cd src/json && xxd -i port_defaults > ports.h
	sed -i src/json/ports.h -e 's/unsigned/inline unsigned/g'

	# default.json -> remove whitespace -> array of chars
	sed src/default.json -z -e 's/\([^aA-zZ]\)\s*/\1/g' > src/json/config_default
	cd src/json && xxd -i config_default > config.h
	sed -i src/json/config.h -e 's/unsigned/inline unsigned/g'
	
	@# I'd like to make this work:
	@#xxd -i <(sed src/ports.json -z -e 's/\([^aA-zZ]\)\s*/\1/g') > src/json/ports.h