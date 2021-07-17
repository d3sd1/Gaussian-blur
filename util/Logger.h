//
// Created by Andrei García on 8/12/20.
//

#ifndef PROYECTO_PRINCIPAL_MODIFIED_LOGGER_H
#define PROYECTO_PRINCIPAL_MODIFIED_LOGGER_H

class Logger {
public:
    void logHeader(std::string inpPath, std::string outPath) {
        std::cout << "Input path: " + inpPath << std::endl;
        std::cout << "Output path: " + outPath << std::endl;
    }

    void logFileProcess(std::string filePath, int fileReadTime, int gaussFinishTime, int sobelFinishTime, int copyFinishTime,
                        int totalProcessTime) {
        printf("File: \"%s\"(time: %d)", filePath.c_str(), totalProcessTime);
        std::cout << "" << std::endl;
        printf("Load time: %d", fileReadTime);
        std::cout << "" << std::endl;
        if (gaussFinishTime > 0) {
            printf("Gauss time: %d", gaussFinishTime);
            std::cout << "" << std::endl;
        }
        if (sobelFinishTime > 0) {
            printf("Sobel time: %d", sobelFinishTime);
            std::cout << "" << std::endl;
        }
        if (copyFinishTime > 0) {
            printf("Store time: %d", copyFinishTime);
            std::cout << "" << std::endl;
        }
    }
};

#endif //PROYECTO_PRINCIPAL_MODIFIED_LOGGER_H
