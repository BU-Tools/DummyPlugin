# Dummy Plugin

This is a dummy plugin for BUTool. 

## DummyTextIO

DummyTextIO is a class from which the plugin class publicly inherits and through which all plugin output passes in order to fulfill printing operations.

## Build instructions 

Clone BUTool, then checkout this code into `plugins/` directory. Then follow BUTool buold instructions.


## Use
from the BUTool directory:
```
source plugins/DummyPlugin/env.sh
./bin/tool/BUTool.exe
add_device DUMMY
```

## How it works - overview
Upon instantiation of DUMMY in BUTool, the user calls `AddStream`, which adds a unique_ptr<ostream> to the DummyTextIO `streams` vector. 
    * I am trying to figure out how to use a unique_ptr to a generic ostream object, but for now the `streams` vector is populated with cout objects
    * The idea is to have a vector of different output streams (cout, ofstream, ostringstream, etc)

The DummyTextIO class has a DummyTextController object which handles printing. When the Controller `Print` function is called, the `streams` vector is passed 
by const l-value reference so that the function only access the streams by pointer, and does *not* take ownership of them. This ensures that the unique_ptrs remain in the vector. 

## Example of use
The `streams` vector is empty on initialization, so only the debug cues will show up ("Print() called" sent to console via cout) when `start` function is called. The DummyDevice `start` function simply prints a message using the DummyTextController `Print` function.
```
>add_device DUMMY 
Hello World - from Dummy
>start
Print() called
Print() called
```

Calling addstream puts two unique_ptr<ostream> in the `streams` vector, which are then written to, resulting in the output:
```
>addstream
>addstream
>start
Print() called
message from Controller
message from Controller
Print() called
0x0
0x0
```

The DummyDevice command `resetvector` calls the DummyTextIO function `ResetStreams`, which clears the vector. This is shown when calling `start` after resetting, resulting in no output from the DummyTextController `Print` function:
```
>resetvector 
Print() called
resetting streams vector
>start
Print() called
Print() called
```

## Todo:
* Use generic ostreams to allow for writing to files, stringstreams, etc. 
* Be able to select individual streams to write to
* Determine use case for PrintDebug/Error commands
