# GraphLib (for v1.0)
[![Language](https://img.shields.io/badge/language-C%2B%2B11-green.svg)](https://isocpp.org)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
### A graphic library

## Get started
Graphlib is very easy to learn. This library can open, read, edit and save jpeg images.

## Installation (On linux)
### Build and install the library
To begin download the last release in a directory  
Open a terminal, unzip the release and go into the repository  
Create a lib directory (`mkdir lib`)  
Go into the the build directory (`cd build`)  
The library will be installed into `/usr/local/lib/`  
The headers will be installed into `/usr/local/include/graphlib/`  
Build the library (`make auto`)  
The library will be compiled and installed

### Set the LD_LIBRARY_PATH
The LD_LIBRARY_PATH is `/usr/local/lib/`  
G++ needs it to find the library  
To set it, return at the root of the repository (`cd ..`)  
Set the LD_LIBRARY_PATH running `env.sh` (`. ./env.sh`)  
##### You must run the env.sh command each time you open a terminal (`. ./env.sh`)

## Your first example
Go into the examples directory (`cd /examples/jpeg/`)  
Build the example (`make`)  
Now read the `main.cc` file  
The comments will help you  
To build the programm you need to use this shell line :  
`g++ -Wall -o main main.cc -I/usr/local/include -L/usr/local/lib -lgraph`  
`-Wall` option : show all warnings  
`-I/usr/local/include` option : find the graphlib headers  
`-L/usr/local/lib` option : find the graphlib executable  
`-lgraph` option : include the graphlib

## Errors
If you detected any errors, please contact me in the issues section !
