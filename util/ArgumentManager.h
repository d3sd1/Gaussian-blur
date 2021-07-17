//
// Created by Andrei García on 1/12/20.
//

#ifndef PROYECTO_PRINCIPAL_ARGUMENT_MANAGER_H
#define PROYECTO_PRINCIPAL_ARGUMENT_MANAGER_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "../model/LabArgument.h"
#include "../model/Action.h"
#include "./PathHelper.h"
#include <unistd.h>

namespace fs = std::filesystem;
using namespace std;


class ArgumentManager {
private:
    int argc{0};
    std::string op;
    std::string inpPath;
    std::string outPath;
public:
    explicit ArgumentManager(int argc, char *argv[])
    {
        this->argc = argc;
        this->op = argv[1];
        this->inpPath = argv[2];
        this->outPath = argv[3];
    }

    void checkParamNumber() {
        if (argc != 4) {
            std::cout << "Wrong format:" << std::endl;
            std::cout << "  image-seq operation in_path out_path" << std::endl;
            std::cout << "  operation: copy, gauss, sobel" << std::endl;
            exit(-1);
        }
    }

    Action checkOperation() {
        if (op == "copy") {
            return Action::COPY;
        } else if (op == "gauss") {
            return Action::GAUSS;
        } else if (op == "gauss") {
            return Action::GAUSS;
        } else if (op == "sobel") {
            return Action::SOBEL;
        } else {
            std::cout << "Unexpected operation: " + op << std::endl;
            std::cout << "  image-seq operation in_path out_path" << std::endl;
            std::cout << "  operation: copy, gauss, sobel" << std::endl;
            exit(-1);
        }
    }

    std::string checkInputPath() {
        PathHelper pathHelper;
        if (!pathHelper.isValidPath(inpPath)) {
            std::cout << "Input path: " + inpPath << std::endl;
            std::cout << "Output path: " + outPath << std::endl;
            std::cout << "Cannot open directory [" + inpPath + "]" << std::endl;
            std::cout << "  image-seq operation in_path out_path" << std::endl;
            std::cout << "  operation: copy, gauss, sobel" << std::endl;
            exit(-1);
        }
        return inpPath;
    }

    std::string checkOutputPath() {
        PathHelper pathHelper;
        if (!pathHelper.isValidPath(outPath)) {
            std::cout << "Input path: " + inpPath << std::endl;
            std::cout << "Output path: " + outPath << std::endl;
            std::cout << "Output directory [" + outPath + "] does not exist" << std::endl;
            std::cout << "  image-seq operation in_path out_path" << std::endl;
            std::cout << "  operation: copy, gauss, sobel" << std::endl;
            exit(-1);
        }
        return outPath;
    }
};

#endif //PROYECTO_PRINCIPAL_ARGUMENT_MANAGER_H
