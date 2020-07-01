all:
	g++ -o main main.cc graphlib/jpeg/openSave.cc graphlib/jpeg/readEdit.cc graphlib/jpeg/jpeg.h -ljpeg
clean:
	rm main
