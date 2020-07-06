all:
	g++ -o main main.cc graphlib/jpeg/openSave.cc graphlib/jpeg/getPixel.cc graphlib/jpeg/resizeCrop.cc graphlib/jpeg/setPixel.cc graphlib/jpeg/jpeg.h -ljpeg
	./main
clean:
	rm main
