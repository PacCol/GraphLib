all:
	g++ -o main main.cc graphlib/jpeg/jpeg.cc graphlib/jpeg/jpeg.h -ljpeg
clean:
	rm main
