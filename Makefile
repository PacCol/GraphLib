all:
	g++ -o main main.cc graphlib/jpeg.cc graphlib/jpeg.h -ljpeg
clean:
	rm main
