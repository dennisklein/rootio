## Download and Compile

```
$ git clone https://github.com/dennisklein/rootio
$ cd rootio
rootio$ cmake -S. -Bbuild
rootio$ cmake --build build
```

## Run

Generate a file with 500000 events of size 1 KiB each (adjust the event size in the file `event.hpp`):

```
rootio$ build/rio w events.root 500000
493.021 MiB (516970075 bytes) in 37.8421 seconds (13.0284 MiB/s).
```

Read all events with a read cache size of 16 MiB (adjust the cache size in the file `read.cpp`)

```
rootio$ build/rio r events.root
493.021 MiB (516970075 bytes) in 15.656 seconds (31.4909 MiB/s).
```
