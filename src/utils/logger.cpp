#include <iostream>

#include "src/utils/logger.h"

using namespace tinyraytracer;
using std::string;
using std::cout;
using std::endl;

void Logger::debug(const std::string& m)
{
#ifndef NDEBUG
    cout << "[DEBUG] " << m << endl;
#endif
}

void Logger::message(const std::string& m)
{
    cout << "[ MSG ] " << m << endl;
}

void Logger::error(const std::string& m)
{
    cout << "[ERROR] " << m << endl;
}
