int readJpegImage(char* fileName);

class jpegImage {
public:
    explicit jpegImage(char* fileName);
    int width;
    int height;
    int pixelSize;
};
