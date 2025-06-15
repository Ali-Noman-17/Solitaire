#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class Logger {
    string fileName;
    ofstream file;
public:
    Logger();
    Logger(string file);
    ~Logger();
    void flush();
    void destroy();
    void writeError(const string error_message);
};

#endif LOGGER_H