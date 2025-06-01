#include "gtest/gtest.h"
#include "../include/LoggerCore.h"
#include <fstream>
#include <cstdio>

class TestableLoggerCore : public LoggerCore {
public:
    TestableLoggerCore(const std::string& filename) : LoggerCore(filename) {}
    
    using LoggerCore::logHelper;
    using LoggerCore::currentDateTime;
};

class LoggerCoreTest : public ::testing::Test {
protected:
    void SetUp() override {
        testFile = "test.log";
        core = new TestableLoggerCore(testFile);
    }

    void TearDown() override {
        delete core;
        std::remove(testFile.c_str());
    }

    std::string testFile;
    TestableLoggerCore* core;
};

TEST_F(LoggerCoreTest, LogsMessageToFile) {
    std::string message = "Test message";
    std::string level = "TEST";
    
    core->logHelper(message, level);
    
    std::ifstream file(testFile);
    std::string line;
    std::getline(file, line);
    
    EXPECT_TRUE(line.find(message) != std::string::npos);
    EXPECT_TRUE(line.find(level) != std::string::npos);
}

TEST_F(LoggerCoreTest, CurrentDateTimeReturnsValidFormat) {
    std::string dt = core->currentDateTime();
    EXPECT_EQ(dt.length(), 19); // YYYY-MM-DD HH:MM:SS
    EXPECT_EQ(dt[4], '-');
    EXPECT_EQ(dt[7], '-');
    EXPECT_EQ(dt[10], ' ');
    EXPECT_EQ(dt[13], ':');
    EXPECT_EQ(dt[16], ':');
}
