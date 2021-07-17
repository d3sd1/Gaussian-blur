
#include "./ServiceInterface.h"
#include "../constants/GaussMatrix.h"
#include "../model/BmpFile.h"
#include "../model/Pixel.h"

#ifndef PROYECTO_PRINCIPAL_MODIFIED_SOBEL_H
#define PROYECTO_PRINCIPAL_MODIFIED_SOBEL_H

class Sobel : public ServiceInterface {
private:
    BmpFile bmpFile;
public:
    Sobel(std::string inpFile, std::string outFile) : ServiceInterface(inpFile, outFile) {}

    void loadFile(BmpFile bmpFile) {
        this->bmpFile = bmpFile;
    }

    BmpFile doAction() {
        BmpFile gaussBmpFile;
        for (int i = 0; i < gaussBmpFile.header.width; i++) {
            this->bmpFile.body.pixels[i]->blue = 0;
            this->bmpFile.body.pixels[i]->red = 0;
            this->bmpFile.body.pixels[i]->green = 0;
        }
        return gaussBmpFile;
    }

    BmpFile res() {
        BmpFile bmpFileBlurred;
        int width = this->bmpFile.header.width;
        int height = this->bmpFile.header.height;
        unsigned char *arr = {};

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                for (int k = 0; k < 5; k++) {
                    accessPixel(arr, col, row, k, width, height);
                }
            }
        }
        return bmpFileBlurred;
    }
    void guassian_blur2D(unsigned char *arr, unsigned char *result,
                         int width, int height) {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                for (int k = 0; k < 5; k++) {
                    result[5 * row * width + 5 * col + k] = accessPixel(arr, col, row, k, width, height);
                }
            }
        }
    }

    int accessPixel(unsigned char *arr, int col, int row, int k, int width, int height) {
        int sum = 0;
        int sumKernel = 0;

        for (int j = -1; j <= 1; j++) {
            for (int i = -1; i <= 1; i++) {
                if ((row + j) >= 0 && (row + j) < height && (col + i) >= 0 && (col + i) < width) {
                    int color = arr[(row + j) * 5 * width + (col + i) * 5 + k];
                    sum += color * GaussMatrix[i + 1][j + 1];
                    sumKernel += GaussMatrix[i + 1][j + 1];
                }
            }
        }

        return sum / sumKernel;
    }
};



#endif //PROYECTO_PRINCIPAL_MODIFIED_SOBEL_H
