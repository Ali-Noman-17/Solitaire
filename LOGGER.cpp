#include "LOGGER.h"

Logger::Logger() {}

Logger::Logger(const string file): fileName(file) {
    flush();
}

Logger::~Logger() {}

void Logger::flush() {
    file.open(fileName, ios::trunc);
    file.close();
}

void Logger::writeError(const string error_message) {
    file.open(fileName, ios::app);
    if (!file.is_open()) return; //error
    time_t now = time(nullptr);
    char timestamp[26];
    ctime_s(timestamp, 26, &now);
    int len = strlen(timestamp);
    timestamp[len - 1] = '\0';
    file << "[" << timestamp << "]  " << error_message << "\n";
    file.close();
}