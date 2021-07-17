#ifndef BMP_FILE_H
#define BMP_FILE_H
#include "./BmpHeader.h"
#include "./BmpBody.h"

struct BmpFile {
    BmpHeader header;
    BmpBody body;
};


#endif //BMP_FILE_H
