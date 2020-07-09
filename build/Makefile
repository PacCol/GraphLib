LIB_DIR := /usr/local/lib/
INCLUDE_DIR := /usr/local/include/

MAJOR := 1
MINOR := 0
RELEASE := $(MAJOR).$(MINOR)

.PHONY : all
all: libgraph.$(RELEASE).a libgraph.so.$(RELEASE)

.PHONY : clean
clean :
	rm -f *.o libgraph.so.$(RELEASE) libgraph.$(RELEASE).a

%.o: ../src/*/%.cc
	g++ -Wall -fPIC -o $@ -c $<

# JPEG Image
OBJ := getPixel.o imageInformations.o openSave.o resizeCrop.o setPixel.o convertToGrayscale.o

# face detector
OBJ := $(OBJ) initDetector.o detectFaces.o

libgraph.so.$(RELEASE): $(OBJ)
	g++ -Wall -shared -Wl,-soname,libgraph.so.$(MAJOR) -o libgraph.so.$(RELEASE) $(OBJ) -ljpeg
	rm -f ../lib/libgraph*
	cp libgraph.so.$(RELEASE) ../lib
	cp libgraph.$(RELEASE).a ../lib
	(cd ../lib && ln -s libgraph.so.$(RELEASE) libgraph.so.$(MAJOR))
	(cd ../lib && ln -s libgraph.so.$(MAJOR) libgraph.so)

libgraph.$(RELEASE).a: $(OBJ)
	ar -cvq libgraph.$(RELEASE).a $+

install:
	mkdir -p $(INCLUDE_DIR)graphlib
	install -m 644 -o root -g root ../src/jpeg/jpeg.h ../src/detector/detector.h -t $(INCLUDE_DIR)graphlib
	install -m 644 -o root -g root ../lib/libgraph.so.$(RELEASE) ../lib/libgraph.$(RELEASE).a -t $(LIB_DIR)
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
