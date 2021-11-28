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
- read url & port config
    - **Library Options**
        - https://github.com/nlohmann/json
        - boost::json
    - two files:
        - ports (community defined)
        - urls (user defined)
- check for font color compatibility within linux terminals
- python handler
- boost::test or similar