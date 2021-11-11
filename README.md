# ServerStatus

A small linux command line utility to check the status of one or more servers across common ports

It's like nmap but quicker to use!

## Building

### Dependencies
curl

```
make
bin/main
```

## TODOs:
    - read url & port config
        - https://github.com/nlohmann/json
        - two files:
            - ports (community defined)
            - urls (user defined)
    - ping w/out curl (src/ping.cpp)
    - python handler
