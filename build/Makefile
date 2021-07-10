LIB_DIR := /usr/lib/
INCLUDE_DIR := /usr/include/

.PHONY : all
all: libgraph.so

.PHONY : clean
clean :
	rm -f *.o libgraph.so

%.o: ../src/%.cc
	g++ -Wall -g -fPIC -o $@ -c $<

# Image basics
OBJ := initialization.o jpeg.o getPixel.o resizeCrop.o setPixel.o convertToGrayscale.o

# Image filters
OBJ := $(OBJ) medianFilter.o gaussianFilter.o cannyFilter.o

libgraph.so: $(OBJ)
	g++ -Wall -shared -Wl,-soname,libgraph.so -o libgraph.so $(OBJ) -ljpeg
	rm -f ../lib/libgraph*

install:
	install -m 644 -o root -g root ../src/graphlib.h -t $(INCLUDE_DIR)
	rm -f $(LIB_DIR)libgraph.so
	cp libgraph.so $(LIB_DIR)

uninstall:
	rm -f $(LIB_DIR)libgraph*
	rm -f $(INCLUDE_DIR)graphlib.h

auto:
	make clean
	make all
	make install
