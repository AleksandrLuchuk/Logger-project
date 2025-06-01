cmake_minimum_required(VERSION 3.14)
project(LoggerProject)

# Включаем FetchContent для загрузки GTest
include(FetchContent)

# Настраиваем загрузку GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# Явно включаем возможность загрузки
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(googletest)

# Проверяем, что GTest загрузился
if(NOT googletest_POPULATED)
  message(FATAL_ERROR "Failed to fetch googletest!")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${googletest_SOURCE_DIR}/include ${googletest_SOURCE_DIR})
# Статическая библиотека
add_library(logger_static STATIC
    src/LoggerCore.cpp
    src/Logger.cpp
)
target_include_directories(logger_static PUBLIC include)

# Исполняемый файл
add_executable(logger_app src/main.cpp)
target_link_libraries(logger_app logger_static pthread)

# Тесты
enable_testing()

# Тест для LoggerCore
add_executable(test_logger_core tests/test_logger_core.cpp)
target_link_libraries(test_logger_core
    logger_static
    gtest_main  
    pthread
)
add_test(NAME test_logger_core COMMAND test_logger_core)

# Тест для Logger
add_executable(test_logger tests/test_logger.cpp)
target_link_libraries(test_logger
    logger_static
    gtest_main
    pthread
)
add_test(NAME test_logger COMMAND test_logger)
