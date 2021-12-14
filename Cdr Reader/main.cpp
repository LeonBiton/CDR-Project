#include <iostream>
#include "cdrextractor.hpp"

int main(){
    char buffer[100];
    char ip[20] = "127.0.0.1";
    UpdateServer updateServer(2008, ip);
    updateServer.ConnectToServer();
    CdrExtractor extract("cdr.txt" ,  updateServer);
    extract.ExtractCdr();

    return 0;
}