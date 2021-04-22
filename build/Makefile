LIB_DIR := /usr/local/lib/
INCLUDE_DIR := /usr/local/include/

MAJOR := 1
MINOR := 0
RELEASE := $(MAJOR).$(MINOR)

.PHONY : all
all: libgraph.so.$(RELEASE)

.PHONY : clean
clean :
	rm -f *.o libgraph.so.$(RELEASE)

%.o: ../src/%.cc
	g++ -Wall -g -fPIC -o $@ -c $<

# Image
OBJ := initialization.o jpeg.o imageInformations.o getPixel.o resizeCrop.o setPixel.o convertToGrayscale.o alphaChannel.o

# Image filters
OBJ := $(OBJ) medianFilter.o gaussianFilter.o cannyFilter.o

libgraph.so.$(RELEASE): $(OBJ)
	g++ -Wall -shared -Wl,-soname,libgraph.so.$(MAJOR) -o libgraph.so.$(RELEASE) $(OBJ) -ljpeg
	rm -f ../lib/libgraph*
	cp libgraph.so.$(RELEASE) ../lib
	(cd ../lib && ln -s libgraph.so.$(RELEASE) libgraph.so.$(MAJOR))
	(cd ../lib && ln -s libgraph.so.$(MAJOR) libgraph.so)

install:
	mkdir -p $(INCLUDE_DIR)graphlib
	install -m 644 -o root -g root ../src/graphlib.h -t $(INCLUDE_DIR)graphlib/
	rm -f $(LIB_DIR)libgraph.so
	rm -f $(LIB_DIR)libgraph.so.$(MAJOR)
	(cd $(LIB_DIR) && ln -s libgraph.so.$(RELEASE) libgraph.so.$(MAJOR))
	(cd $(LIB_DIR) && ln -s libgraph.so.$(MAJOR) libgraph.so)

uninstall:
	rm -f $(LIB_DIR)libgraph*
	rm -rf $(INCLUDE_DIR)graphlib

auto:
	make clean
	make all
	make install
	make clean
