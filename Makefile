all:
	g++ -o main main.cc graphlib/jpeg/openClose.cc graphlib/jpeg/readWrite.cc graphlib/jpeg/jpeg.h -ljpeg
clean:
	rm main
