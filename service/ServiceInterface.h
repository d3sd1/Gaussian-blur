

#ifndef PROYECTO_PRINCIPAL_MODIFIED_SERVICEINTERFACE_H
#define PROYECTO_PRINCIPAL_MODIFIED_SERVICEINTERFACE_H

class ServiceInterface {
protected:
    std::string inpFile;
    std::string outFile;
public:
    ServiceInterface(std::string inpFile, std::string outFile) {
        this->inpFile = inpFile;
        this->outFile = outFile;
    }

   virtual BmpFile doAction() = 0;
};

#endif //PROYECTO_PRINCIPAL_MODIFIED_SERVICEINTERFACE_H
