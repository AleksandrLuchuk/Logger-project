#include "Logger.h"
#include <stdexcept>

const std::string Logger::Debug = "DEBUG";
const std::string Logger::Info = "INFO";
const std::string Logger::Error = "ERROR";

const char* const Logger::kLogFileName = "application.log";
Logger* Logger::pInstance = nullptr;

Logger& Logger::instance() {
    static Cleanup cleanup;
    std::lock_guard<std::mutex> guard(LoggerCore::sMutex);
    if (pInstance == nullptr)
        pInstance = new Logger();
    return *pInstance;
}

Logger::Cleanup::~Cleanup() {
    std::lock_guard<std::mutex> guard(LoggerCore::sMutex);
    delete Logger::pInstance;
    Logger::pInstance = nullptr;
}

Logger::Logger() : LoggerCore(kLogFileName) {}

void Logger::log(const std::string& inMessage, const std::string& inLogLevel) {
    logHelper(inMessage, inLogLevel);
}

void Logger::log(const std::vector<std::string>& inMessages, const std::string& inLogLevel) {
    for (const auto& message : inMessages) {
        logHelper(message, inLogLevel);
    }
}
