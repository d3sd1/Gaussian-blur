#include "./ServiceInterface.h"

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <fstream>

#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int


#ifndef PROYECTO_PRINCIPAL_MODIFIED_COPY_H
#define PROYECTO_PRINCIPAL_MODIFIED_COPY_H

class Copy : public ServiceInterface {
//private:
    //BmpFile bmpFile
public:
    Copy(std::string inpFile, std::string outFile) : ServiceInterface(inpFile, outFile) {}
/*
    void loadFile(BmpFile bmpFile) {
        this->bmpFile = bmpFile;
    }*/

    BmpFile doAction() {
        BmpFile copiedFile;
        return copiedFile;
    }
    void simpleCopy() {
        std::ifstream src(this->inpFile, std::ios::binary);
        std::ofstream dst(this->outFile, std::ios::binary);
        dst << src.rdbuf();
    }
};

#endif //PROYECTO_PRINCIPAL_MODIFIED_COPY_H
