#include <unistd.h>
#include <exception>

#include <string>
#include <filesystem>
#include <fstream>
#include "../util/Timer.h"
#include "../util/FileReader.h"
#include "../util/Timer.h"
#include "../util/Logger.h"
#include "../service/Gauss.h"
#include "../service/Copy.h"
#include "../service/Sobel.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include <errno.h>
#include <omp.h>
#include <iostream>
#include <algorithm>

#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int

namespace fs = std::filesystem;

#ifndef PROYECTO_PRINCIPAL_MODIFIED_PATHHELPER_H
#define PROYECTO_PRINCIPAL_MODIFIED_PATHHELPER_H
#define THREAD_NUM 16

class PathHelper {
public:
    bool isValidPath(std::string path) {
        int result = access(&path[0], W_OK);
        return result == 0;
    }

    void scanFolder(std::string inpPath, std::string outPath, Action op) {
        FileReader fileReader;
        Timer timer;
        Logger log;

        for (const auto &entry : fs::directory_iterator(inpPath)) {
            int startProcessTime = timer.currentMillis(), totalProcessTime = 0,
                    gaussFinishTime = 0,
                    sobelFinishTime = 0,
                    copyFinishTime = 0;

            std::string filePath = entry.path();
            std::filesystem::path p(filePath);
            std::string fileName = p.filename();
            std::string inpFile = inpPath + '/' + fileName;
            std::string outFile = outPath + '/' + fileName;

            if (fileName.substr(fileName.size() - 4) == ".bmp") {
                int fileReadStartTime = timer.currentMillis();
                BmpFile bmpFile = fileReader.fileToObj(filePath);
                int fileReadTime = timer.currentMillis() - fileReadStartTime;

                int gaussStartTime = timer.currentMillis();
                if (op == Action::GAUSS || op == Action::SOBEL) {
                    Gauss gauss(inpPath, outPath);
                    gauss.loadFile(bmpFile);
                    gauss.doAction();
                    gaussFinishTime = timer.currentMillis() - gaussStartTime;
                }

                int sobelStartTime = timer.currentMillis();
                if (op == Action::SOBEL) {
                    Sobel sobel(inpPath, outPath);
                    sobel.doAction();
                    sobelFinishTime = timer.currentMillis() - sobelStartTime;
                }

                int copyStartTime = timer.currentMillis();
                if (op == Action::COPY || op == Action::GAUSS || op == Action::SOBEL) {
                    Copy copy(inpFile, outFile);
                    copy.doAction();
                    copyFinishTime = timer.currentMillis() - copyStartTime;
                }

                totalProcessTime = timer.currentMillis() - startProcessTime;

                log.logFileProcess(filePath, fileReadTime, gaussFinishTime, sobelFinishTime, copyFinishTime,
                                   totalProcessTime);

            }
        }
    }

    void scanFolderParallel(std::string inpPath, std::string outPath, Action op) {

        FileReader fileReader;
        Timer timer;
        Logger log;

        for (const auto &entry : fs::directory_iterator(inpPath)) {
#pragma omp parallel
            {
                int startProcessTime = timer.currentMillis(), totalProcessTime = 0,
                        gaussFinishTime = 0,
                        sobelFinishTime = 0,
                        copyFinishTime = 0;

                std::string filePath = entry.path();
                std::filesystem::path p(filePath);
                std::string fileName = p.filename();
                std::string inpFile = inpPath + '/' + fileName;
                std::string outFile = outPath + '/' + fileName;

                if (fileName.substr(fileName.size() - 4) == ".bmp") {
                    int fileReadStartTime = timer.currentMillis();
                    BmpFile bmpFile = fileReader.fileToObj(filePath);
                    int fileReadTime = timer.currentMillis() - fileReadStartTime;

                    int gaussStartTime = timer.currentMillis();
                    if (op == Action::GAUSS || op == Action::SOBEL) {
                        Gauss gauss(inpPath, outPath);
                        gauss.loadFile(bmpFile);
                        gauss.doAction();
                        gaussFinishTime = timer.currentMillis() - gaussStartTime;
                    }

                    int sobelStartTime = timer.currentMillis();
                    if (op == Action::SOBEL) {
                        Sobel sobel(inpPath, outPath);
                        sobel.doAction();
                        sobelFinishTime = timer.currentMillis() - sobelStartTime;
                    }

                    int copyStartTime = timer.currentMillis();
                    if (op == Action::COPY || op == Action::GAUSS || op == Action::SOBEL) {
                        Copy copy(inpFile, outFile);
                        copy.doAction();
                        copyFinishTime = timer.currentMillis() - copyStartTime;
                    }

                    totalProcessTime = timer.currentMillis() - startProcessTime;

                    log.logFileProcess(filePath, fileReadTime, gaussFinishTime, sobelFinishTime, copyFinishTime,
                                       totalProcessTime);

                }
            }
        }
    }
};

#endif //PROYECTO_PRINCIPAL_MODIFIED_PATHHELPER_H
