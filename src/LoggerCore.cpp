#include "LoggerCore.h"
#include <ctime>
#include <stdexcept>

std::mutex LoggerCore::sMutex;

LoggerCore::LoggerCore(const std::string& filename) {
    mOutputStream.open(filename, std::ios_base::app);
    if (!mOutputStream.good()) {
        throw std::runtime_error("Unable to initialize the Logger!");
    }
}

LoggerCore::~LoggerCore() {
    mOutputStream.close();
}

void LoggerCore::logHelper(const std::string& inMessage, const std::string& inLogLevel) {
    std::lock_guard<std::mutex> guard(sMutex);
    mOutputStream << currentDateTime() << ": " << inLogLevel << ": " << inMessage << std::endl;
}

std::string LoggerCore::currentDateTime() const {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}
