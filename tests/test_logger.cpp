#include "gtest/gtest.h"
#include "../include/Logger.h"
#include <fstream>
#include <cstdio> // для std::remove
#include <unistd.h> // для access()

class LoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
       // std::remove("application.log"); // Удаляем старый лог-файл
    }

    bool fileExists(const std::string& filename) {
        return access(filename.c_str(), F_OK) == 0;
    }

    bool fileContains(const std::string& filename, const std::string& content) {
        std::ifstream file(filename);
        if (!file) return false;
        
        std::string line;
        while (std::getline(file, line)) {
            if (line.find(content) != std::string::npos) {
                return true;
            }
        }
        return false;
    }
};

TEST_F(LoggerTest, SingletonInstanceWorks) {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    std::cout << "Current working directory: " << cwd << std::endl;

    Logger& logger1 = Logger::instance();
    Logger& logger2 = Logger::instance();
    EXPECT_EQ(&logger1, &logger2);
}

TEST_F(LoggerTest, LogsSingleMessage) {
    Logger::instance().log("Test message", Logger::Debug);
    
    // Проверяем что файл существует
    ASSERT_TRUE(fileExists("application.log")) << "Log file was not created";
    
    // Проверяем содержимое файла
    EXPECT_TRUE(fileContains("application.log", "Test message"));
    EXPECT_TRUE(fileContains("application.log", Logger::Debug));
}

TEST_F(LoggerTest, LogsMultipleMessages) {
    std::vector<std::string> messages = {"Message 1", "Message 2"};
    Logger::instance().log(messages, Logger::Error);
    
    ASSERT_TRUE(fileExists("application.log"));
    
    bool found1 = false, found2 = false;
    std::ifstream file("application.log");
    std::string line;
    
    while (std::getline(file, line)) {
        if (line.find("Message 1") != std::string::npos) found1 = true;
        if (line.find("Message 2") != std::string::npos) found2 = true;
    }
    
    EXPECT_TRUE(found1) << "'Message 1' not found in log";
    EXPECT_TRUE(found2) << "'Message 2' not found in log";
    EXPECT_TRUE(fileContains("application.log", Logger::Error));
}
