# ServerStatus

A small linux command line utility to check the status of one or more servers across common ports

It's like nmap but quicker to use!

## Building
```
make
bin/main
```

### Dependencies
curl

## TODOs:
- read url & port config
    - **Library Options**
        - https://github.com/nlohmann/json
        - boost::json
    - two files:
        - ports (community defined)
        - urls (user defined)
- ping w/out curl (src/ping/ping.cpp)
- python handler
- boost::test or similar