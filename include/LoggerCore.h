#ifndef _LOGGER_CORE_H_
#define _LOGGER_CORE_H_

#include <string>
#include <fstream>
#include <mutex>

class LoggerCore {
    friend class LoggerCoreTest;
protected:
    LoggerCore(const std::string& filename);
    virtual ~LoggerCore();
    
    void logHelper(const std::string& inMessage, const std::string& inLogLevel);
    std::string currentDateTime() const;
    
    LoggerCore(const LoggerCore&) = delete;
    LoggerCore& operator=(const LoggerCore&) = delete;
    static std::mutex sMutex;
    std::ofstream mOutputStream;
};

#endif /* _LOGGER_CORE_H_ */
