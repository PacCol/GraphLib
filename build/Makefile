LIB_DIR := lib
LIB_NAME := graph

auto:
	make clean
	make all
	make install

.PHONY : all
all: libgraph.a libgraph.so.1.0

.PHONY : clean
clean :
	rm -f *.o libgraph.so.1.0 libgraph.a

%.o: ../src/jpeg/%.cc ../src/jpeg/jpeg.h
	g++ -Wall -fPIC -o $@ -c $<

OBJ := getPixel.o imageInformations.o openSave.o resizeCrop.o setPixel.o

libgraph.so.1.0: $(OBJ)
	g++ -Wall -shared -Wl,-soname,libgraph.so.1 -o libgraph.so.1.0 $(OBJ) -ljpeg
	rm -f ../lib/libgraph*
	cp libgraph.so.1.0 ../lib
	(cd ../lib && ln -s libgraph.so.1.0 libgraph.so.1)
	(cd ../lib && ln -s libgraph.so.1 libgraph.so)

libgraph.a: $(OBJ)
	ar -cvq libgraph.a $+

install:
	install -m 644 -o root -g root ../lib/libgraph.so.1.0 libgraph.a -t /usr/local/lib
	install -m 644 -o root -g root ../src/jpeg/jpeg.h -t /usr/local/include/
