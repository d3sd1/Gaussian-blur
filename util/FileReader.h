#ifndef FILE_READER_H
#define FILE_READER_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <fstream>
#include <stdint.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <vector>
#include "../model/BmpFile.h"
#include "../model/BmpHeader.h"
#include "../model/BmpBody.h"
#include "../model/Pixel.h"
#include "../exception/BmpFileException.h"

namespace fs = std::filesystem;
using namespace std;

class FileReader {
private:
    BmpHeader getHeader(FILE *f) {
        unsigned char info[54];
        fread(info, sizeof(unsigned char), 54, f);
        BmpHeader header;
        header.fileSize = *(unsigned int *) &info[2];
        header.dataStart = *(unsigned int *) &info[10];
        header.width = *(unsigned int *) &info[18];
        header.height = *(unsigned int *) &info[22];
        header.planes = *(unsigned short *) &info[26];//Hay que usar short ya que int son 4B y planes ocupa 2B
        header.compression = *(unsigned int *) &info[30];
        header.imageSize = *(unsigned int *) &info[34];
        return header;
    }

    BmpBody getBody(FILE *f, BmpHeader header) {
        BmpBody bmpBody;

        Pixel **pixels = new Pixel *[header.width];
        for (int i = 0; i < header.width; ++i) {
            pixels[i] = new Pixel[header.height];
        }

        fseek(f, header.dataStart, SEEK_SET);
        for (int i = 0; i < header.width; i++) {
            for (int j = 0; j < header.height; j++) {
                fread(&pixels[i][j].red, 1, 1, f);
                fread(&pixels[i][j].green, 1, 1, f);
                fread(&pixels[i][j].blue, 1, 1, f);
            }
        }
        bmpBody.pixels = pixels;
        return bmpBody;
    }

public:
    FileReader() {}

    BmpFile fileToObj(std::string fileNameStr) {
        char *fileName = new char[fileNameStr.length() + 1];
        strcpy(fileName, fileNameStr.c_str());

        FILE *f = fopen(fileName, "rb");


        BmpFile bmpFile;
        bmpFile.header = getHeader(f);
        bmpFile.body = getBody(f, bmpFile.header);
        fclose(f);
        delete[] fileName;

        if (bmpFile.header.planes != 1) {
            throw (BmpFileException("The planes number on the image must be 1.", -12, -34));
        } else if (bmpFile.header.compression != 0) {
            throw (BmpFileException("Compression value must be 0.", -12, -34));
        }
        // TODO HANDLE -> El tamaño de cada punto debe ser de 24 bits.

        return bmpFile;
    }

    void objToFile() {
        /*
         * Cabecera de fichero: 14 bytes (bytes 0 a 13)
Byte 0: Código ascii del carácter 'B'.
Byte 1: Código ascii del carácter 'M'.
Bytes 2, 3, 4, 5: Tamaño total.
Bytes 6, 7, 8, 9: Valor 0.
Bytes 10, 11, 12, 13: Valor 54.
Cabecera de información: 40 bytes (bytes 14 a 53)
Bytes 14, 15, 16, 17: Valor 40.
Bytes 18, 19, 20, 21: Número de pixeles de ancho.
Bytes 22, 23, 24, 25: Número de pixeles de alto.
Bytes 26, 27: Valor 1.
Bytes 28, 29: Valor 24.
Bytes 30, 31, 32, 33: Valor 0.
Bytes 34, 35, 36, 37: Tamaño en bytes de la imagen.
Bytes 38, 39, 40, 41: Valor 2835.
Bytes 42, 43, 44, 45: Valor 2835.
Bytes 46, 47, 48, 49: Valor 0.
Bytes 50, 51, 52, 53: Valor 0.


        f = fopen(filename, "rb");
        FILE *pFile = fopen(outFile, "wb");

        unsigned char head[header.dataStart];
        fread(head, sizeof(unsigned char), header.dataStart, f);
        fwrite(head, sizeof(unsigned char), header.dataStart, pFile);

        for (int i = header.height - 1; i >= 0; i--) {
            for (int j = 0; j <= header.width; j++) {
                fwrite(&pixels[i][j].red, sizeof(uint8_t), 1, pFile);
                fwrite(&pixels[i][j].green, sizeof(uint8_t), 1, pFile);
                fwrite(&pixels[i][j].blue, sizeof(uint8_t), 1, pFile);
            }
        }

        fclose(pFile);
        // fclose(f);*/

    }


};


#endif //FILE_READER_H
