# Dummy Plugin

This is a dummy plugin for BUTool. 

## DummyTextIO

DummyTextIO is a class from which the plugin class publicly inherits and through which all plugin output passes in order to fulfill printing operations.

## Build instructions 

Clone BUTool, then checkout this code into `plugins/` directory. Then follow BUTool buold instructions.


## Use

### V0.1
```
source plugins/DummyPlugin/env.sh
add_device DUMMY
addstream
```
addstream adds a cout stream to the `streams` vector