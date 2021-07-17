#ifndef BMP_HEADER_H
#define BMP_HEADER_H

struct BmpHeader {
    int fileSize;
    int dataStart;
    int width;
    int height;
    int planes;
    int compression;
    int imageSize;
};


#endif //BMP_HEADER_H
