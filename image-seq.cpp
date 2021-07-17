
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "util/ArgumentManager.h"
#include "util/FileReader.h"
#include "model/Action.h"
#include "./util/Logger.h"
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <errno.h>

#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int


namespace fs = std::filesystem;
using namespace std;


class ImageSeq {
public:
    void run(int argc, char *argv[]) {
        ArgumentManager argumentManager(argc, argv);
        argumentManager.checkParamNumber();
        Action op = argumentManager.checkOperation();
        string inpPath = argumentManager.checkInputPath();
        string outPath = argumentManager.checkOutputPath();

        Logger logger;
        PathHelper pathHelper;

        logger.logHeader(inpPath, outPath);
        pathHelper.scanFolder(inpPath, outPath, op);

        exit(0);
    }
};

int main(int argc, char *argv[]) {
    ImageSeq imageSeq;
    imageSeq.run(argc, argv);
}