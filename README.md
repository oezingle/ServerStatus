# ServerStatus

A small linux command line utility to check the status of one or more servers across common ports

## Building
```
make
bin/main
```

### Dependencies
unix sockets (any linux has 'em)

## TODOs:
- check for font color compatibility within linux terminals
- FXTUI output (hover for description?)
- integrate src/ports.json in a 'smarter' way - .h file takes 'tons' of memory
- async server pinging/printing
- python handler
- boost::test or similar