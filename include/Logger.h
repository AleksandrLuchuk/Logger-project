#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <vector>
#include <string>
#include "LoggerCore.h"

class Logger : public LoggerCore {
public:
    static const std::string Debug;
    static const std::string Info;
    static const std::string Error;

    static Logger& instance();

    void log(const std::string& inMessage, const std::string& inLogLevel);
    void log(const std::vector<std::string>& inMessages, const std::string& inLogLevel);
    static const char* const kLogFileName;

protected:
    friend class Cleanup;
    class Cleanup {
    public:
        ~Cleanup();
    };

private:
    static Logger* pInstance;

    Logger();
    virtual ~Logger() = default;
};

#endif /* _LOGGER_H_ */
