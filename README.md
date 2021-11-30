# ServerStatus

A small linux command line utility to check the status of one or more servers across common ports

## Building
```
make
bin/main
```

### Dependencies (Building)
- xxd
- sed

## TODOs:
- check for font color compatibility within linux terminals
- FXTUI output (hover for description?)
- python handler
- boost::test or similar
- makefile -> make install -> make build w/ config_dir -> ~/.config/ServerStatus
    - gcc -D<var> defines a macro while compiling