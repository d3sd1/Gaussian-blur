//
// Created by Andrei García on 1/12/20.
//

#ifndef PROYECTO_PRINCIPAL_LABARGUMENT_H
#define PROYECTO_PRINCIPAL_LABARGUMENT_H

#include <iostream>

class LabArgument {
public:
    std::string execMode;
public:
    std::string inputPath;
public:
    std::string outputPath;
public:
    LabArgument() {
        execMode = "";
        inputPath = "";
        outputPath = "";
    }
};

#endif //PROYECTO_PRINCIPAL_LABARGUMENT_H
