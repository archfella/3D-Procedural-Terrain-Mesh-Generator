// Original code copyright (C) 2014 Etay Meiri
// Modified by Filip Radovic in 2024
// Licensed under the GNU General Public License v3
// See LICENSE file in the project root for details.

#include "utils.h"

int getFileSize(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if(!file) {
        std::cout << "Error opening the file!\n" << std::endl;
        return -1;
    }

    //  Seek to the end of the file
    fseek(file, 0, SEEK_END);

    //  Get the current position in the file
    int fileSize = ftell(file);

    fclose(file);

    return fileSize;
}

char* ReadFile(const char* filename, int& size) {
    FILE* file = fopen(filename, "rb"); //  read in binary mode
    if(!file) {
        std::cout << "Error opening the file!\n" << std::endl;
        exit(-1);
    }

    size = getFileSize(filename);

    char* p = (char*)malloc(size);
    size_t bytesRead = fread(p, 1, size, file);

    if(bytesRead != size) {
        std::cout << "Error reading the file\n" << std::endl;
        exit(-2);
    }

    fclose(file);
    return p;
}