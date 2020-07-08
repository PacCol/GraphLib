# GraphLib
### A graphic library

## Get started
Graphlib is very easy to learn. This library can open, read, modify and save jpeg images.

## Installation (On linux)
### Build and install the library
To begin download the repository in a directory  
Create a lib directory (`mkdir lib`)  
Go into the the build directory (`cd build`)  
Edit the Makefile (with your text editor)  
Choose the include directory and the library directory (INCLUDE_DIR, LIB_DIR)  
```
LIB_DIR := /usr/local/lib/
INCLUDE_DIR := /usr/local/include/
```
The LIB_DIR is the directory where the library will be saved  
The INCLUDE_DIR is the directory where the headers will be saved
#### If you don't know this, just keep this parameters
Close the Makefile  
Build the library (`make auto`)  
The library will be compiled and installed  

### Set the LD_LIBRARY_PATH
The LD_LIBRARY_PATH is the `LIB_DIR`  
To set it, return at the root of the repository (`cd ..`)  
if you don't changed the `LIB_DIR`, set the LD_LIBRARY_PATH (`. ./env.sh`)  
Else you can change the parameter editing the file  
`export LD_LIBRARY_PATH=/usr/local/lib`  
Now you can change the LD_LIBRARY_PATH

## How to learn
Check out the example : `examples/jpeg/main.cc`
